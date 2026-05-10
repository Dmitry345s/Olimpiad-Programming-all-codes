#include<bits/stdc++.h>

using namespace std;

int mod = 1e9 + 7;

signed main() {
    int n, k, x;
    cin >> n >> x >> k;
    vector<vector<array<int, 2>>> dp(x, (vector<array<int, 2>> (k + 1, {0, 0})));
    for (int i = 0; i < x; ++i) {
        dp[i][0][0] = 1;
    }
    vector<vector<array<int, 2>>> suf(x, vector<array<int, 2>> (k + 1, {0, 0}));
    for (int i = 1; i < n; ++i) {
        for (int j = x - 1; j >= 0; --j) {
            for (int l = 0; l <= k; ++l) {
                if (j == x - 1) {
                    suf[j][l] = dp[j][l];
                } else {
                    suf[j][l][0] = (suf[j + 1][l][0] + dp[j][l][0]);
                    if (suf[j][l][0] >= mod) suf[j][l][0] -= mod;
                    suf[j][l][1] = (suf[j + 1][l][1] + dp[j][l][1]);
                    if (suf[j][l][1] >= mod) suf[j][l][1] -= mod;
                }
            }
        }
        //vector<vector<array<int, 2>>> ndp(x, (vector<array<int, 2>> (k + 1, {0, 0})));
        for (int j = 0; j < x; ++j) {
            for (int l = 0; l <= k; ++l) {
                dp[j][l][0] = suf[j][l][0];
                if (dp[j][l][0] >= mod) dp[j][l][0] -= mod;
                dp[j][l][0] += dp[j][l][1];
                if (dp[j][l][0] >= mod) dp[j][l][0] -= mod;
                dp[j][l][1] = suf[0][l][0] + suf[0][l][1];
                if (dp[j][l][1] >= mod) dp[j][l][1] -= mod;
                dp[j][l][1] -= suf[j][l][0];
                if (dp[j][l][1] < 0) dp[j][l][1] += mod;
                dp[j][l][1] -= suf[j][l][1];
                if (dp[j][l][1] < 0) dp[j][l][1] += mod;
                if (l != 0 && j != x - 1) {
                    dp[j][l][0] += suf[j + 1][l - 1][1];
                    if (dp[j][l][0] >= mod) dp[j][l][0] -= mod;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < x; ++i) {
        ans += dp[i][k][0];
        if (ans >= mod) ans -= mod;
        ans += dp[i][k][1];
        if (ans >= mod) ans -= mod;
    }
    cout << ans << endl;
    return 0;
}
