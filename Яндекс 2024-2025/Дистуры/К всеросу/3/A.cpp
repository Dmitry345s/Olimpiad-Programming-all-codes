#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e9;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int ans = INF;
    for (int now = 0; now <= m; ++now) {
        vector<vector<int>> dp(n + 1, vector<int> (now + 1, INF));
        dp[0][0] = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j <= now; ++j) {
                int x = abs(i + 1 - j) % k;
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j] + (x != 0) * a[i]);
                int y = abs(n - 1 - (now - j - 1)) % k;
                if (j < now) {
                    dp[i + 1][j + 1] = min(dp[i + 1][j + 1], dp[i][j] + (y != k - 1) * a[i]);
                }
            }
        }
        ans = min(ans, dp[n][now]);
        //cout << now << " " << dp[n][now] << endl;
    }
    cout << ans << endl;
    return 0;
}
