#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> t(n), d(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i] >> d[i] >> c[i];
    }
    if (m == 0) {
        cout << 0 << endl;
        return 0;
    }
    vector<vector<int>> dp(n, vector<int> (3));
    dp[0] = {t[0], d[0], c[0]};
    for (int i = 1; i < n; ++i) {
        for (int j = i; j >= 0; --j) {
            if (j == 0) {
                int sum1 = abs(dp[0][0]) + abs(dp[0][1]) + abs(dp[0][2]);
                int sum2 = abs(t[i]) + abs(d[i]) + abs(c[i]);
                if (sum2 >= sum1) {
                    dp[0] = {t[i], d[i], c[i]};
                }
            } else {
                int sum1 = abs(dp[j][0]) + abs(dp[j][1]) + abs(dp[j][2]);
                int sum2 = abs(dp[j - 1][0] + t[i]) + abs(dp[j - 1][1] + d[i]) + abs(dp[j - 1][2] + c[i]);
                if (sum2 >= sum1) {
                    dp[j] = {dp[j - 1][0] + t[i], dp[j - 1][1] + d[i], dp[j - 1][2] + c[i]};
                }
            }
            cout << j << " " << dp[j][0] << " " << dp[j][1] << " " << dp[j][2] << endl;
        }
    }
    cout << abs(dp[m - 1][0]) + abs(dp[m - 1][1]) + abs(dp[m - 1][2]) << endl;
    return 0;
}
