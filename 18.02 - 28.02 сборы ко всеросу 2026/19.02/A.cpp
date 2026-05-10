#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

signed main() {
    int n, m;
    cin >> n >> m;
    int s, t;
    cin >> s >> t;
    --s; --t;
    int sum = 0;
    vector<vector<vector<int>>> g(n);
    vector<vector<int>> mn(n, vector<int> (n, INF));
    while (sum < m) {
        int u, k;
        cin >> u >> k;
        --u;
        vector<int> now(k);
        for (int i = 0; i < k; ++i) {
            cin >> now[i];
            --now[i];
            mn[u][now[i]] = min(mn[u][now[i]], i);
        }
        g[u].push_back(now);
        sum += k;
    }
    int yy = n + 1;
    vector<vector<int>> dp(n, vector<int> (yy, INF));
    set<pair<int, pair<int, int>>> q;
    dp[s][0] = 0;
    q.insert({dp[s][0], {s, 0}});
    while (!q.empty()) {
        auto [ds, v] = *q.begin();
        //cout << ds << " " << v.first << " " << v.second << endl;
        q.erase(q.begin());
        auto [rv, t] = v;
        int num = dp[rv][t] - t;
        for (int u = 0; u < n; ++u) {
            if (mn[rv][u] == INF) continue;
            int i = mn[rv][u];
            int nowds = dp[rv][t] + max(i - t, 1);
            int y = nowds - num - i;
            if (y > n) continue;
            if (nowds < dp[u][y]) {
                q.erase({dp[u][y], {u, y}});
                dp[u][y] = nowds;
                q.insert({dp[u][y], {u, y}});
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < yy; ++i) {
        ans = min(ans, dp[t][i]);
    }
    cout << ans << endl;
    return 0;
}
