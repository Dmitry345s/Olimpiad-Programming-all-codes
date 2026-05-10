#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<int> p(MAX);

int root(int v) {
    if (v == p[v]) {
        return v;
    }
    return p[v] = root(p[v]);
}

int ln = 18;
vector<vector<pair<int, int>>> g(MAX), up(ln, vector<pair<int, int>> (MAX));
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v, int p = 0, int c = 0) {
    up[0][v] = {p, c};
    for (int i = 1; i < ln; ++i) {
        up[i][v].first = up[i - 1][up[i - 1][v].first].first;
        up[i][v].second = max(up[i - 1][v].second, up[i - 1][up[i - 1][v].first].second);
    }
    tin[v] = timer++;
    for (auto [to, w] : g[v]) {
        if (to == p) continue;
        dfs(to, v, w);
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[a] >= tin[b] && tout[b] >= tout[a];
}

int lca(int a, int b) {
    int minm = 0;
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(b, up[i][a].first)) {
            minm = max(minm, up[i][a].second);
            a = up[i][a].first;
        }
    }
    if (!ch(b, a)) {
        minm = max(minm, up[0][a].second);
    }
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(a, up[i][b].first)) {
            minm = max(minm, up[i][b].second);
            b = up[i][b].first;
        }
    }
    if (!ch(a, b)) {
        minm = max(minm, up[0][b].second);
    }
    return minm;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    vector<array<int, 3>> g2;
    vector<int> used(m);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g2.push_back({c, a, b});
    }
    sort(g2.begin(), g2.end());
    int sum = 0;
    for (int i = 0; i < m; ++i) {
        auto[w, v, to] = g2[i];
        if (root(v) != root(to)) {
            g[v].push_back({to, w});
            g[to].push_back({v, w});
            p[root(v)] = root(to);
            sum += w;
            used[i] = 1;
        }
    }
    dfs(0);
    int ans2 = 1e9;
    for (int i = 0; i < m; ++i) {
        if (used[i]) continue;
        auto [w, v, to] = g2[i];
        int x = lca(v, to);
        ans2 = min(ans2, sum - x + w);
    }
    cout << sum << " " << ans2 << endl;
    return 0;
}
