#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (k == n) {
        int ans = 0;
        for (int i = 0; i < n - 1; ++i) {
            ans += (a[i] ^ a[i + 1]);
        }
        cout << ans << endl;
    } else {
        vector<vector<int>> dp(n + 1, vector<int> (k + 1));
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i][1] = 0;
            for (int j = 1; j < i; ++j) {
                for (int u = 1; u < k; ++u) {
                    dp[i][u + 1] = max(dp[i][u + 1], dp[j][u] + (a[j - 1] ^ a[i - 1]));
                }
            }
            ans = max(ans, dp[i][k]);
        }
        cout << ans << endl;
    }
    return 0;
}
