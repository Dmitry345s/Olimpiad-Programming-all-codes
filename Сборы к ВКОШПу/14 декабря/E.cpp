#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    vector<vector<int>> dp(30, vector<int> (30));
    dp[0][0] = 1;
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            if (i + j >= 29) continue;
            dp[i + 1][j] += dp[i][j];
            dp[i][j + 1] += dp[i][j];
        }
    }
    for (int i = 0; i < 15; ++i) {
        cout << dp[i][29 - i] << endl;
    }
    return 0;
}
