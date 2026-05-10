#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5 + 5;
vector<int> p(MAX);

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

int ln = 18;
vector<vector<pair<int, int>>> g(MAX);
vector<vector<pair<int, int>>> up(ln, vector<pair<int, int>> (MAX, {1, 0}));
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v, int p = 1, int c = 0) {
    up[0][v] = {p, c};
    tin[v] = timer++;
    for (int i = 1; i < ln; ++i) {
        up[i][v].first = up[i - 1][up[i - 1][v].first].first;
        up[i][v].second = max(up[i - 1][up[i - 1][v].first].second, up[i - 1][v].second);
    }
    for (auto [to, w] : g[v]) {
        if (to == p) continue;
        dfs(to, v, w);
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[b] <= tin[a] && tout[b] >= tout[a];
}

int lca(int a, int b) {
    int maxm = 0;
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(b, up[i][a].first)) {
            maxm = max(maxm, up[i][a].second);
            a = up[i][a].first;
        }
    }
    if (!ch(b, a)) {
        maxm = max(maxm, up[0][a].second);
    }
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(a, up[i][b].first)) {
            maxm = max(maxm, up[i][b].second);
            b = up[i][b].first;
        }
    }
    if (!ch(a, b)) {
        maxm = max(maxm, up[0][b].second);
    }
    return maxm;
}

signed main() {
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 1; i <= n; ++i) {
        p[i] = i;
    }
    for (int i = m; i >= 1; --i) {
        for (int j = 2 * i; j <= n; j += i) {
            if (root(i) != root(j)) {
                g[i].push_back({j, m + 1 - i});
                g[j].push_back({i, m + 1 - i});
                p[root(j)] = root(i);
            }
        }
    }
    dfs(1);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        if (a == b) {
            cout << 0 << endl;
            continue;
        }
        cout << lca(a, b) << endl;
    }
    return 0;
}
