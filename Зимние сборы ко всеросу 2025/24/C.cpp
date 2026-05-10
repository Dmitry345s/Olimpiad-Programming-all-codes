#include<bits/stdc++.h>

using namespace std;

vector<vector<int>> solve1(vector<vector<int>> a, int n) {
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cnt[j] += a[i][j];
        }
    }
    sort(cnt.begin(), cnt.end());
    vector<vector<int>> ans(n, vector<int> (n));
    for (int j = 0; j < n; ++j) {
        for (int i = n - 1; i >= n - cnt[j]; --i) {
            ans[i][j] = 1;
        }
    }
    return ans;
}

vector<vector<int>> solve2(vector<vector<int>> a, int n) {
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cnt[i] += a[i][j];
        }
    }
    sort(cnt.begin(), cnt.end());
    vector<vector<int>> ans(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = n - 1; j >= n - cnt[i]; --j) {
            ans[i][j] = 1;
        }
    }
    return ans;
}

vector<vector<int>> solve3(vector<vector<int>> a, int n) {
    vector<vector<int>> ans(n, vector<int> (n));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - i; j < n; ++j) {
            ans[i][j] = 1;
        }
    }
    for (int i = 0; i < n / 2; ++i) {
        ans[n - i - 1][i] = 1;
    }
    return ans;
}

vector<vector<int>> solve4(vector<vector<int>> a, int n) {
    vector<vector<int>> ans(n, vector<int> (n));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = n - i; j < n; ++j) {
            ans[i][j] = 1;
        }
    }
    for (int i = n / 2; i < n; ++i) {
        ans[n - i - 1][i] = 1;
    }
    return ans;
}

const int MAX = 101, INF = 1e9;
short int dp[MAX][MAX][MAX * MAX];
//short int pr[MAX][MAX][MAX * MAX];
short int mxm[MAX][MAX][MAX * MAX];

vector<vector<int>> solve5(vector<vector<int>> a, int n, int u) {
    vector<vector<int>> pref(n, vector<int> (n + 1));
    for (int j = 0; j < n; ++j) {
        pref[j][0] = 0;
        for (int i = 0; i < n; ++i) {
            pref[j][i + 1] = pref[j][i] + (u - a[i][j]);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int sum = 0; sum <= n * n; ++sum) {
                dp[i][j][sum] = -1;
                mxm[i][j][sum] = -1;
            }
        }
    }
    for (int j = n; j >= 0; --j) {
        dp[0][j][j] = pref[0][j];
        if (j != n) {
            int x = mxm[0][j + 1][j];
            if (x == -1 || dp[0][j][j] >= dp[0][x][j]) {
                x = j;
            }
            mxm[0][j][j] = x;
            for (int j2 = j; j2 >= 0; --j2) {
                mxm[0][j2][j] = x;
            }
        } else {
            mxm[0][j][j] = n;
            for (int j2 = j; j2 >= 0; --j2) {
                mxm[0][j2][j] = n;
            }
        }
    }
    for (int i = 1; i < n; ++i) {
        for (int j = n; j >= 0; --j) {
            for (int sum = j; sum <= n * (i + 1); ++sum) {
                if (sum - j > n * i) continue;
                int j2 = mxm[i - 1][j][sum - j];
                if (j2 != -1 && dp[i][j][sum] <= dp[i - 1][j2][sum - j] + pref[i][j] && dp[i - 1][j2][sum - j] != -1) {
                    dp[i][j][sum] = dp[i - 1][j2][sum - j] + pref[i][j];
                }
                if (j != n) {
                    int x = mxm[i][j + 1][sum];
                    if (dp[i][j][sum] >= dp[i][x][sum]) {
                        x = j;
                    }
                    mxm[i][j][sum] = x;
                } else {
                    mxm[i][j][sum] = n;
                }
            }
        }
    }
    int mxm2 = 0;
    int now = 0;
    for (int j = 0; j <= n; ++j) {
        if (mxm2 <= dp[n - 1][j][n * n / 2]) {
            mxm2 = dp[n - 1][j][n * n / 2];
            now = j;
        }
    }
    int nsm = n * n / 2;
    vector<int> st(n);
    for (int i = n - 1; i >= 0; --i) {
        st[i] = now;
        if (i > 0) {
            int x = now;
            now = mxm[i - 1][now][nsm - now];
            nsm -= x;
        }
    }
    vector<vector<int>> ans(n, vector<int> (n, 1));
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < st[j]; ++i) {
            ans[i][j] = 0;
        }
    }
    return ans;
}

signed main() {
    int t, n, k1, k2;
    cin >> t >> n >> k1 >> k2;
    vector<vector<int>> a(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> ans;
    const int K = 3;
    if (n < 300) {
        ans = solve5(a, n, 1);
    } else {
        vector<vector<int>> b(n / K, vector<int> (n / K));
        for (int i = 0; i < n; i += K) {
            for (int j = 0; j < n; j += K) {
                for (int i2 = 0; i2 < K; ++i2) {
                    for (int j2 = 0; j2 < K; ++j2) {
                        b[i / K][j / K] += a[i + i2][j + j2];
                    }
                }
            }
        }
        ans = solve5(b, n / K, K * K);
        vector<vector<int>> rans(n, vector<int> (n));
        for (int i = 0; i < n; i += K) {
            for (int j = 0; j < n; j += K) {
                for (int i2 = 0; i2 < K; ++i2) {
                    for (int j2 = 0; j2 < K; ++j2) {
                        if (ans[i / K][j / K]) {
                            rans[i + i2][j + j2] = 1;
                        }
                    }
                }
            }
        }
        ans = rans;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
