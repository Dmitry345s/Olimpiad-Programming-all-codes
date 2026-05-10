#include<bits/stdc++.h>

using namespace std;

signed main() {
    vector<int> dp(100);
    dp[0] = 1;
    for (int i = 0; i < 9; ++i) {
        vector<int> newdp(100, 0);
        for (int j = 0; j < 10; ++j) {
            for (int l = 0; l < 100 - j; ++l) {
                newdp[l + j] += dp[l];
            }
        }
        dp = newdp;
    }
    int s;
    dp[1] += 1;
    cin >> s;
    cout << dp[s] << endl;
    return 0;
}
