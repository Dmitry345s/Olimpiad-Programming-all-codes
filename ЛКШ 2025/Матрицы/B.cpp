#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> f(n + 1, vector<char> (m + 1, '#'));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> f[i][j];
        }
    }
    vector<vector<int>> dp(n + 1, vector<int> (m + 1));
    dp[2][1] = (f[2][1] == '.');
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 2 && j == 1) continue;
            if (f[i][j] == '.') {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % MOD;
            }
        }
    }
    vector<vector<int>> dp2(n + 1, vector<int> (m + 1));
    dp2[1][2] = (f[1][2] == '.');
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (i == 1 && j == 2) continue;
            if (f[i][j] == '.') {
                dp2[i][j] = (dp2[i - 1][j] + dp2[i][j - 1]) % MOD;
            }
        }
    }
    //cout << dp[n][m] << " " << dp2[n][m] << endl;
    int one = (dp[n][m - 1] * dp2[n - 1][m]) % MOD;
    int sec = (dp[n - 1][m] * dp2[n][m - 1]) % MOD;
    cout << (one - sec + MOD) % MOD << endl;
    return 0;
}
