#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 42, C = 10, MOD = (int)1e9 + 7;

int dp[MAX][MAX][MAX][C][2];

signed main() {
    int n, m;
    cin >> n >> m;
    vector<string> f(n);
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < C; ++k) {
                dp[m][i][j][k][1] = 1;
                if (i == j) {
                    dp[m][i][j][k][1] = 0;
                    dp[m][i][j][k][0] = 1;
                }
            }
        }
    }
    for (int sl = m - 1; sl >= 0; --sl) {
        for (int d = 0; d < n; ++d) {
            for (int l = 0; l < n - d; ++l) {
                int r = l + d;
                for (int c = 0; c < C; ++c) {
                    if (c > 0) dp[sl][l][r][c][0] += dp[sl][l][r][c - 1][0];
                    if (c > 0) dp[sl][l][r][c][1] += dp[sl][l][r][c - 1][1];
                    int u = r;
                    while (u >= l && (f[u][sl] == '?' || f[u][sl] - '0' == c)) {
                        if (u == l) {
                            dp[sl][l][r][c][0] += dp[sl + 1][l][r][C - 1][0];
                            dp[sl][l][r][c][1] += dp[sl + 1][l][r][C - 1][1];
                        } else if (c > 0) {
                            dp[sl][l][r][c][1] += (dp[sl][l][u - 1][c - 1][1] * dp[sl + 1][u][r][C - 1][1]) % MOD;
                            dp[sl][l][r][c][1] += (dp[sl][l][u - 1][c - 1][1] * dp[sl + 1][u][r][C - 1][0]) % MOD;
                            dp[sl][l][r][c][1] += (dp[sl][l][u - 1][c - 1][0] * dp[sl + 1][u][r][C - 1][1]) % MOD;
                            dp[sl][l][r][c][0] += (dp[sl][l][u - 1][c - 1][0] * dp[sl + 1][u][r][C - 1][0]) % MOD;
                        }
                        u--;
                    }
                    dp[sl][l][r][c][0] %= MOD;
                    dp[sl][l][r][c][1] %= MOD;
                    //cout << sl << " " << l << " " << r << " " << c << " " << dp[sl][l][r][c][0] << " " << dp[sl][l][r][c][1] << endl;
                }
            }
        }
    }
    cout << dp[0][0][n - 1][C - 1][0] << endl;
    return 0;
}
