#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= min(4, i); ++j) {
            dp[i] = max(dp[i], dp[i - j]);
        }
        if (i >= 5) {
            dp[i] = max(dp[i], dp[i - 5] + a[i - 4] + a[i - 3] + a[i - 2] + a[i - 1] + a[i - 5]);
        }
    }
    cout << dp[n] * 10 << endl;
    return 0;
}
