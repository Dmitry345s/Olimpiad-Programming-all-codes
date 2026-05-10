#include<bits/stdc++.h>

using namespace std;

const int MAX = 500, INF = 2e9, LN = 30;

struct Edge {
    int v, c;
    Edge(int v = 0, int c = 0) : v(v), c(c) {}
};

vector<Edge> ed;
vector<int> g[MAX];

void add(int v, int u, int c) {
    g[v].push_back((int)ed.size());
    ed.push_back(Edge(u, c));
    g[u].push_back((int)ed.size());
    ed.push_back(Edge(v, 0));
}

void upd(int in, int x) {
    ed[in].c -= x;
    ed[(in ^ 1)].c += x;
}

int get_fl(int in) {
    return ed[(in ^ 1)].c;
}

int t;
int used[MAX];

int dfs(int v, int fl, int k) {
    used[v] = 1;
    if (fl == 0) return fl;
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
    }
    t = n - 1;
    long long ans = 0;
    for (int i = LN - 1; i >= 0; --i) {
        while (true) {
            fill(used, used + n, 0);
            int fl = dfs(0, INF, i);
            ans += fl;
            if (fl == 0) break;
        }
    }
    cout << ans << endl;
    for (int i = 0; i < 2 * m; i += 2) {
        cout << get_fl(i) << endl;
    }
    return 0;
}
