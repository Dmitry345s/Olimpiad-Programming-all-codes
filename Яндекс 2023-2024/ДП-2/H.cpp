#include<bits/stdc++.h>

using namespace std;

signed main() {
    freopen("coloring.in", "r", stdin);
    freopen("coloring.out", "w", stdout);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> g(n, vector<int> (n));
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a][b] = 1;
            g[b][a] = 1;
        }
        vector<int> ch(n, -1);
        vector<pair<int, vector<int>>> dp(1 << n, {1e9, ch});
        dp[0].first = -1;
        for (int mask = 0; mask < (1 << n); ++mask) {
            //cout << mask << endl;
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) continue;
                vector<int> tr(n);
                for (int j = 0; j < n; ++j) {
                    if (!((mask >> j) & 1)) continue;
                    if (!g[i][j]) continue;
                    //cout << mask << " " << j << " " << dp[mask].second[j] << endl;
                    tr[dp[mask].second[j]] = 1;
                }
                int get = -1;
                for (int j = 0; j < n; ++j) {
                    if (!tr[j]) {
                        get = j;
                        break;
                    }
                }
                //cout << mask << " " << i << " " << get << endl;
                if (max(get, dp[mask].first) < dp[mask ^ (1 << i)].first) {
                    dp[mask ^ (1 << i)].first = max(get, dp[mask].first);
                    dp[mask ^ (1 << i)].second = dp[mask].second;
                    dp[mask ^ (1 << i)].second[i] = get;
                }
            }
        }
        cout << dp.back().first + 1 << endl;
        for (int i = 0; i < n; ++i) {
            cout << dp.back().second[i] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
