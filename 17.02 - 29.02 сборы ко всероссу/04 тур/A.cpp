#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    int s, t, ds, k;
    cin >> s >> t >> ds >> k;
    --s; --t;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    vector<int> d(n, 1e18);
    set<pair<int, int>> q;
    d[s] = 0;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [to, c] : g[v]) {
            if (d[to] > d[v] + c) {
                q.erase({d[to], to});
                d[to] = d[v] + c;
                q.insert({d[to], to});
            }
        }
    }
    vector<int> d2(n, 1e18);
    d2[t] = 0;
    q.insert({0, t});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [to, c] : g[v]) {
            if (d2[to] > d2[v] + c) {
                q.erase({d2[to], to});
                d2[to] = d2[v] + c;
                q.insert({d2[to], to});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        if (d[i] + d2[i] <= k) {
            cout << 1ll * n * (n - 1) / 2 << endl;
            return 0;
        }
    }
    sort(d2.begin(), d2.end());
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int p = k - d[i] - ds;
        int j = upper_bound(d2.begin(), d2.end(), p) - d2.begin();
        ans += j;
    }
    cout << ans << endl;
    return 0;
}
