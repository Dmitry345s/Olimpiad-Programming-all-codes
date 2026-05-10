#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 1;
vector<pair<int, int>> g[MAX];
int c[MAX], used[MAX];
int fl = 1;

void dfs(int v, int cl, int u) {
    c[v] = cl;
    used[v] = 1;
    for (auto [w, to] : g[v]) {
        if (w >= u) continue;
        if (used[to]) {
            if (c[to] == cl) {
                fl = 0;
            }
        } else {
            dfs(to, (cl ^ 1), u);
        }
    }
}

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        vector<array<int, 3>> all;
        for (int i = 0; i < m; ++i) {
            int a, b, w;
            cin >> a >> b >> w;
            g[a].push_back({w, b});
            g[b].push_back({w, a});
            all.push_back({w, a, b});
        }
        int minm = 5e9;
        for (int i = 0; i < n; ++i) {
            sort(g[i].begin(), g[i].end());
            if ((int)g[i].size() > 1) {
                minm = min(minm, g[i][0].first + g[i][1].first);
            }
        }
        int l = 1, r = minm + 1;
        while (l + 1 < r) {
            int u = (l + r) / 2;
            fl = 1;
            fill(used, used + n, 0);
            fill(c, c + n, -1);
            for (int i = 0; i < n; ++i) {
                if (!used[i]) {
                    dfs(i, 0, u);
                }
            }
            if (fl) {
                l = u;
            } else {
                r = u;
            }
        }
        if (l > (int)2e9) {
            cout << "INF" << endl;
        } else {
            cout << l << endl;
        }
    }
    return 0;
}
