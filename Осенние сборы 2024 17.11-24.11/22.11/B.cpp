#include<bits/stdc++.h>

using namespace std;

const int MX = 51, INF = 500;

int dp[MX][MX][MX][MX];

int solve1(vector<int> a, int n) {
    for (int i = 0; i < MX; ++i) {
        for (int i2 = 0; i2 < MX; ++i2) {
            for (int i3 = 0; i3 < MX; ++i3) {
                for (int i4 = 0; i4 < MX; ++i4) {
                    dp[i][i2][i3][i4] = -500;
                }
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        dp[i][i][a[i]][a[i]] = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        dp[i][i + 1][a[i]][a[i]] = 1;
        dp[i][i + 1][a[i + 1]][a[i + 1]] = 1;
        if (a[i] <= a[i + 1]) {
            dp[i][i + 1][a[i]][a[i + 1]] = 2;
        }
        if (a[i] >= a[i + 1]) {
            dp[i][i + 1][a[i + 1]][a[i]] = 2;
        }
    }
    for (int len = 3; len <= n; ++len) {
        for (int l = 0; l < n; ++l) {
            int r = (l + len - 1);
            if (r >= n) break;
            dp[l][r][a[l]][a[l]] = 1;
            dp[l][r][a[r]][a[r]] = 1;
            dp[l][r][min(a[l], a[r])][max(a[l], a[r])] = 2;
            for (int j = 0; j < MX; ++j) {
                for (int j2 = j; j2 < MX; ++j2) {
                    if (j2 <= a[r]) {
                        dp[l][r][j][a[r]] = max(dp[l][r][j][a[r]], dp[l][r - 1][j][j2] + 1);
                    }
                    dp[l][r][j][j2] = max(dp[l][r][j][j2], dp[l][r - 1][j][j2]);
                }
            }
            for (int j = 0; j < MX; ++j) {
                for (int j2 = j; j2 < MX; ++j2) {
                    if (a[l] <= j) {
                        dp[l][r][a[l]][j2] = max(dp[l][r][a[l]][j2], dp[l + 1][r][j][j2] + 1);
                    }
                    dp[l][r][j][j2] = max(dp[l][r][j][j2], dp[l + 1][r][j][j2]);
                }
            }
            for (int j = 0; j < MX; ++j) {
                for (int j2 = j; j2 < MX; ++j2) {
                    int x1 = min(a[l], a[r]);
                    int x2 = max(a[l], a[r]);
                    if (x1 <= j && j2 <= x2) {
                        dp[l][r][x1][x2] = max(dp[l + 1][r - 1][j][j2] + 2, dp[l][r][x1][x2]);
                    }
                    if (x1 <= j) {
                        dp[l][r][x1][j2] = max(dp[l][r][x1][j2], dp[l + 1][r - 1][j][j2] + 1);
                    }
                    if (j2 <= x2) {
                        dp[l][r][j][x2] = max(dp[l][r][j][x2], dp[l + 1][r - 1][j][j2] + 1);
                    }
                    swap(x1, x2);
                    if (x1 <= j) {
                        dp[l][r][x1][j2] = max(dp[l][r][x1][j2], dp[l + 1][r - 1][j][j2] + 1);
                    }
                    if (j2 <= x2) {
                        dp[l][r][j][x2] = max(dp[l][r][j][x2], dp[l + 1][r - 1][j][j2] + 1);
                    }
                }
            }
            /*for (int j = 0; j <= n; ++j) {
                for (int j2 = j; j2 <= n; ++j2) {
                    cout << l << " " << r << " " << j << " " << j2 << " " << dp[l][r][j][j2] << endl;
                }
            }*/
        }
    }
    int ans = 0;
    for (int j = 0; j < MX; ++j) {
        for (int j2 = j; j2 < MX; ++j2) {
            ans = max(ans, dp[0][n - 1][j][j2]);
        }
    }
    return ans;
}

int nvp(vector<int> a, int n) {
    vector<vector<int>> dp1(n, vector<int> (MX));
    dp1[0][a[0]] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < MX; ++j) {
            dp1[i][j] = max(dp1[i - 1][j], dp1[i][j]);
            if (j <= a[i]) {
                dp1[i][a[i]] = max(dp1[i][a[i]], dp1[i - 1][j] + 1);
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < MX; ++i) {
        ans = max(dp1.back()[i], ans);
    }
    return ans;
}

int solve2(vector<int> a, int n) {
    int ans = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        vector<int> b = a;
        vector<int> tsw;
        for (int j = 0; j < n; ++j) {
            if ((mask >> j) & 1) {
                tsw.push_back(j);
            }
        }
        for (int i = 0; i < (int)tsw.size() / 2; ++i) {
            swap(b[tsw[i]], b[tsw[(int)tsw.size() - i - 1]]);
        }
        ans = max(ans, nvp(b, n));
    }
    return ans;
}

mt19937 rnd(time(0));

pair<vector<int>, int> gen() {
    int n = rnd() % 20 + 1;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = rnd() % 20 + 1;
    }
    return {a, n};
}

signed main() {
    /*int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }*/
    while (true) {
        auto [a, n] = gen();
        int x1 = solve1(a, n);
        int x2 = solve2(a, n);
        if (x1 != x2) {
            cout << "WA" << endl;
            cout << n << endl;
            cout << x1 << " " << x2 << endl;
            for (int i = 0; i < n; ++i) {
                cout << a[i] << " ";
            }
            cout << endl;
            break;
        }
        cout << "OK" << endl;
    }
    //cout << solve1(a, n) << endl;
    //cout << n << endl;
    return 0;
}
