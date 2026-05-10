#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;
const int MAX = 1000;
int f[MAX];
int rf[MAX];

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (1ll * ans * a) % MOD;
        }
        x /= 2;
        a = (1ll * a * a) % MOD;
    }
    return ans;
}

int c(int k, int n) {
    return (1ll * f[n] * rf[k]) % MOD * 1ll * rf[n - k] % MOD;
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }
    vector<int> rs(n), s(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        rs[p[i]] = s[i];
        b.push_back(s[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i) {
        rs[i] = lower_bound(b.begin(), b.end(), rs[i]) - b.begin();
    }
    /*int dp[n][n][k][(int)b.size() + 1][(int)b.size() + 1];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int u = 0; u <= k; ++u) {
                for (int t = 0; t < (int)b.size(); ++t) {
                    for (int t2 = 0; t2 < (int)b.size(); ++t2) {
                        dp[i][j][u][t][t2] = 0;
                    }
                }
            }
        }
    }*/
    k = min(k, n);
    int dp[n + 1][n + 1][2][2];
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < k + 1; ++j) {
            for (int u = 0; u < 2; ++u) {
                for (int y = 0; y < 2; ++y) {
                    dp[i][j][u][y] = 0;
                }
            }
        }
    }
    f[0] = 1;
    rf[0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i] = (1ll * f[i - 1] * i) % MOD;
        rf[i] = (1ll * rf[i - 1] * fpow(i, MOD - 2)) % MOD;
    }
    dp[1][1][1][1] = 1;
    dp[0][0][0][0] = 1;
    for (int i = 2; i <= n; ++i) {
        for (int lsz = 0; lsz < i; ++lsz) {
            int t = c(lsz, i - 1);
            //cout << lsz << " " << i << " " << t << endl;
            int rsz = i - 1 - lsz;
            for (int kl = 0; kl <= n; ++kl) {
                for (int kr = 0; kr <= n - kl; ++kr) {
                    for (int c1 = 0; c1 < 2; ++c1) {
                        for (int c2 = 0; c2 < 2; ++c2) {
                            for (int c3 = 0; c3 < 2; ++c3) {
                                for (int c4 = 0; c4 < 2; ++c4) {
                                    int nowans = kl + kr - c2 - c3 + 1;
                                    if (nowans > k) continue;
                                    int lc = c1;
                                    if (lsz == 0) {
                                        lc = 1;
                                    } else if (lsz == 1) {
                                        lc = 0;
                                    }
                                    int rc = c4;
                                    if (rsz == 0) {
                                        rc = 1;
                                    } else if (rsz == 1) {
                                        rc = 0;
                                    }
                                    dp[i][nowans][lc][rc] = (dp[i][nowans][lc][rc] + (1ll * dp[lsz][kl][c1][c2] * dp[rsz][kr][c3][c4]) % MOD * t) % MOD;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i <= k; ++i) {
        for (int c1 = 0; c1 < 2; ++c1) {
            for (int c2 = 0; c2 < 2; ++c2) {
                //cout << i << " " << c1 << " " << c2 << " " << dp[n][i][c1][c2] << endl;
                ans = (ans + dp[n][i][c1][c2]) % MOD;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
