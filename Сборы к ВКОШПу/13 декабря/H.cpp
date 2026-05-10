#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, l;
    cin >> n >> l;
    vector<int> d(n);
    vector<vector<int>> all(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> d[i] >> c;
        for (int j = 0; j < c; ++j) {
            int s;
            cin >> s;
            all[i].push_back(s);
        }
    }
    vector<int> dp((1 << n));
    dp[0] = 0;
    for (int mask = 0; mask < (1 << n); ++mask) {
        for (int j = 0; j < n; ++j) {
            if ((mask >> j) & 1) continue;
            int u = upper_bound(all[j].begin(), all[j].end(), dp[mask]) - all[j].begin() - 1;
            if (u < 0) continue;
            dp[mask + (1 << j)] = max(dp[mask + (1 << j)], all[j][u] + d[j]);
        }
    }
    int ans = n + 1;
    for (int mask = 0; mask < (1 << n); ++mask) {
        if (dp[mask] < l) continue;
        int cnt = 0;
        for (int j = 0; j < n; ++j) {
            if ((mask >> j) & 1) {
                cnt++;
            }
        }
        ans = min(ans, cnt);
    }
    if (ans == n + 1) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
