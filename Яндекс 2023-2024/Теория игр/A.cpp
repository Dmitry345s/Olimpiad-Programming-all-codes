#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> dp(n, vector<int> (m));
    dp[n - 1][m - 1] = 1;
    for (int sum = n + m - 2; sum >= 0; --sum) {
        for (int i = n - 1; i >= 0; --i) {
            int j = sum - i;
            if (j < 0 || j > m - 1) continue;
            int flag = 0;
            for (int j2 = j + 1; j2 < m; ++j2) {
                flag |= dp[i][j2];
            }
            for (int i2 = i + 1; i2 < n; ++i2) {
                flag |= dp[i2][j];
            }
            for (int del = 1; i + del < n && j + del < m; ++del) {
                flag |= dp[i + del][j + del];
            }
            dp[i][j] = !flag;
        }
    }
    cout << dp[0][0] + 1 << endl;
    return 0;
}
