#include<iostream>
#include<vector>
#include<set>

using namespace std;

int main() {
    freopen("kefir.in", "r", stdin);
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int l = 0; l < m; ++l) {
        int i, j, c;
        cin >> i >> j >> c;
        g[i - 1].push_back({j - 1, c});
        g[j - 1].push_back({i - 1, c});
    }
    vector<int> d(n, 1e9);
    set<pair<int, int>> q;
    d[0] = 0;
    q.insert({d[0], 0});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i].first, len = g[v][i].second;
            if (d[to] >= d[v] + len) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                q.insert({d[to], to});
            }
        }
    }
    freopen("kefir.out", "w", stdout);
    if (d[n - 1] == 1e9) {
        cout << -1 << endl;
    } else {
        cout << d[n - 1] << endl;
    }
    return 0;
}
