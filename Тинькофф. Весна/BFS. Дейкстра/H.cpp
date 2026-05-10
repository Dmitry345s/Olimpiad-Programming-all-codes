#include<iostream>
#include<cstdio>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

int main() {
    int n, m, s, t;
    freopen("dist.in", "r", stdin);
    cin >> n >> m >> s >> t;
    vector<vector<pair<int, int>>> g(n);
    for (int l = 0; l < m; ++l) {
        int i, j, w;
        cin >> i >> j >> w;
        g[i - 1].push_back({j - 1, w});
        g[j - 1].push_back({i - 1, w});
    }
    set<pair<int, int>> q;
    vector<int> d(n, 1000000000), p(n);
    vector<bool> used(n, false);
    used[s - 1] = true;
    d[s - 1] = 0;
    p[s - 1] = -1;
    q.insert({d[s - 1], s - 1});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i].first, len = g[v][i].second;
            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], to});
            }
        }
    }
    freopen("dist.out", "w", stdout);
    if (d[t - 1] == 1000000000) {
        cout << -1 << endl;
        return 0;
    }
    cout << d[t - 1] << endl;
    vector<int> ans;
    ans.push_back(t - 1);
    int v = t - 1;
    while (p[v] != -1) {
        ans.push_back(p[v]);
        v = p[v];
    }
    cout << ans.size() << endl;
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
}
