#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAX = 100, INF = 1e9;

struct Edge {
    int v, c, w;
    Edge(int v = 0, int c = 0, int w = 0) : v(v), c(c), w(w) {}
};

vector<int> g[MAX];
vector<Edge> ed;

void add_ed(int u, int v, int c, int w) {
    g[u].push_back((int)ed.size());
    ed.push_back(Edge(v, c, w));
    g[v].push_back((int)ed.size());
    ed.push_back(Edge(u, 0, -w));
}

void upd(int in, int x) {
    ed[in].c -= x;
    ed[(in ^ 1)].c += x;
}

int used[MAX];
int d[MAX];
int t;

int dfs(int v, int fl) {
    if (v == t) return fl;
    used[v] = 1;
    //cout << v << " " << fl << endl;
    for (int in : g[v]) {
        auto [to, c, w] = ed[in];
        //cout << d[v] << " " << w << " " << d[to] << endl;
        if (d[v] + w != d[to] || c < 1 || used[to]) continue;
        int x = dfs(to, min(fl, c));
        if (!x) continue;
        upd(in, x);
        return x;
    }
    return 0;
}

void dist(int n) {
    fill(d, d + n, INF);
    d[0] = 0;
    for (int i = 0; i < n; ++i) {
        for (int u = 0; u < n; ++u) {
            for (int in : g[u]) {
                auto [to, c, w] = ed[in];
                if (c == 0) continue;
                d[to] = min(d[to], d[u] + w);
            }
        }
    }
}

ll sl(int n) {
    t = n - 1;
    dist(n);
    ll ans = 0;
    while (true) {
        fill(used, used + n, 0);
        int fl = dfs(0, INF);
        if (!fl) break;
        ans += 1ll * fl * d[t];
        dist(n);
    }
    return ans;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int u, v, c, w;
        cin >> u >> v >> c >> w;
        --u; --v;
        add_ed(u, v, c, w);
    }
    cout << sl(n) << endl;
    return 0;
}
