#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<vector<long long>> dp(n, vector<long long> (10));
    for (int i = 1; i < 10; ++i) {
        dp[0][i] = 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int k = -1; k <= 1; ++k) {
                int ch = j + k;
                if (0 <= ch && ch <= 9) {
                    dp[i + 1][ch] += dp[i][j];
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < 10; ++i) {
        ans += dp.back()[i];
    }
    cout << ans << endl;
    return 0;
}
