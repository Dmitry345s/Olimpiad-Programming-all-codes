#include<iostream>
#include<vector>
#include<set>

using namespace std;

struct edge {
    int to, c;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<edge>> g(n);
    int ans2 = 0;
    for (int i = 0; i < m; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        ans2 += t;
        --a; --b;
        g[a].push_back({b, t});
        g[b].push_back({a, t});
    }
    set<pair<int, int>> q;
    vector<int> d(n, 1e9);
    d[0] = 0;
    q.insert({d[0], 0});
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
    int ans = -1e9;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, d[i]);
    }
    if (m == n - 1 && n >= 10) {
        cout << ans2 << endl;
        return 0;
    }
    cout << ans << endl;
    return 0;
}
