#include<bits/stdc++.h>

using namespace std;

const int MAX = 500, INF = 1e9;

struct Edge {
    int v, c;
    Edge(int v = 0, int c = 0) : v(v), c(c) {}
};

vector<Edge> ed;

void add(int v, int u, int c) {
    ed.push_back(Edge(u, c));
    ed.push_back(Edge(v, 0));
}

void upd(int in, int x) {
    ed[in].c -= x;
    ed[(in ^ 1)].c += x;
}

vector<int> g[MAX];
int used[MAX];
int t;

int dfs(int v, int fl, int k) {
    used[v] = 1;
    if (v == t) return fl;
    for (int in : g[v]) {
        auto [to, c] = ed[in];
        if (used[to] || c < (1 << k)) continue;
        int x = dfs(to, min(fl, c), k);
        if (x == 0) continue;
        upd(in, x);
        return x;
    }
    return 0;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, u, c;
        cin >> v >> u >> c;
        --v; --u;
        add(v, u, c);
        g[v].push_back((int)ed.size() - 2);
        g[u].push_back((int)ed.size() - 1);
    }
    int ans = 0;
    t = n - 1;
    while (true) {
        fill(used, used + n, 0);
        int x = dfs(0, INF, 0);
        ans += x;
        if (!x) break;
    }
    cout << ans << endl;
    return 0;
}
