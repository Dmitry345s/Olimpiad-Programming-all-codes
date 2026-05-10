#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    int s, f;
    cin >> s >> f;
    --s; --f;
    vector<int> d(n, (int)2e9);
    set<pair<int, int>> q;
    d[s] = 0;
    q.insert({0, s});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (auto [to, c] : g[v]) {
            if (d[to] > max(d[v], c)) {
                q.erase({d[to], to});
                d[to] = max(d[v], c);
                q.insert({d[to], to});
            }
        }
    }
    cout << d[f] << endl;
    return 0;
}
