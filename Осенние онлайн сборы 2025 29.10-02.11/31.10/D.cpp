#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        cin >> d[i];
    }
    vector<vector<pair<int, int>>> ps(n);
    for (int i = 0; i < n - 1; ++i) {
        vector<int> prefs(n - i);
        for (int j = i + 1; j < n; ++j) {
            prefs[j - i] = prefs[j - 1 - i] + d[j];
        }
        vector<int> sufs(i + 2);
        for (int j = i; j >= 0; --j) {
            sufs[j] = sufs[j + 1] + d[j];
        }
        int l = 1;
        int r = i;
        while (l < n - i && r >= 0) {
            if (prefs[l] == sufs[r]) {
                ps[i].push_back({r - 1, i + l + 1});
            }
            if (prefs[l] < sufs[r]) {
                l++;
            } else {
                r--;
            }
        }
    }
    vector<vector<int>> dp(n, vector<int> (n));
    for (int i = 0; i < n - 1; ++i) {
        dp[i][0] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            if (j > 0) dp[i][j] = max(dp[i][j], dp[i][j - 1]);
            if (j < i) dp[i][j] = max(dp[i][j], dp[i - 1][j]);
        }
        if (i == n - 1) continue;
        for (int u = 0; u < (int)ps[i].size(); ++u) {
            auto [l, r] = ps[i][u];
            if (!(r < n && l >= 0)) continue;
            dp[r][i + 1] = max(dp[r][i + 1], dp[i][l] + u + 1);
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp[n - 1][i]);
    }
    cout << ans << endl;
    return 0;
}
