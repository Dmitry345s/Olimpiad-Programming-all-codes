#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 4e5;
vector<vector<pair<int, int>>> g(MAX);

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    set<pair<int, int>> q;
    vector<int> d(MAX, 1e18), dp(MAX, 1e18);
    q.insert({0, 0});
    dp[0] = 0;
    d[0] = 0;
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [to, c] : g[v]) {
            dp[to] = min(d[v], dp[to]);
            if (d[to] > d[v] + c) {
                q.erase({d[to], to});
                d[to] = d[v] + c;
                q.insert({d[to], to});
            }
        }
    }
    set<pair<int, int>> q2;
    vector<int> d2(MAX, 1e18), dp2(MAX, 1e18);
    q2.insert({0, n - 1});
    dp2[n - 1] = 0;
    d2[n - 1] = 0;
    while (!q2.empty()) {
        int v = q2.begin()->second;
        q2.erase(q2.begin());
        for (auto [to, c] : g[v]) {
            dp2[to] = min(d2[v], dp2[to]);
            if (d2[to] > d2[v] + c) {
                q2.erase({d2[to], to});
                d2[to] = d2[v] + c;
                q2.insert({d2[to], to});
            }
        }
    }
    int ans = 1e18;
    for (int i = 0; i < n; ++i) {
        ans = min(ans, dp[i] + dp2[i]);
    }
    cout << ans << endl;
    return 0;
}
