#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<vector<pair<int, int>>> g(MAX);
vector<pair<int, int>> g2(MAX);
vector<int> used(MAX);

void dfs(int v, int j) {
    used[v] = 1;
    for (auto [to, i] : g[v]) {
        if (used[to] || i == j || to == g2[j].first || to == g2[j].second) continue;
        dfs(to, j);
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
         int a, b;
         cin >> a >> b;
         --a; --b;
         g[a].push_back({b, i});
         g[b].push_back({a, i});
         g2[i] = {a, b};
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        used.assign(2e3, 0);
        for (int j = 0; j < n; ++j) {
            if (j != g2[i].first && j != g2[i].second) {
                dfs(j, i);
                break;
            }
        }
        for (int j = 0; j < n; ++j) {
            if (used[j] == 0 && j != g2[i].first && j != g2[i].second) {
                ans++;
                break;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
