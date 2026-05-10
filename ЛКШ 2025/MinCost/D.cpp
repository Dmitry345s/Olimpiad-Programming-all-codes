#include<bits/stdc++.h>

#define int long long

using namespace std;
using ll = long long;

const int MAX = 25, INF = 1e9;

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
int d[MAX];

void dist(int n) {
    int nd[n];
    fill(nd, nd + n, INF);
    nd[0] = 0;
    vector<int> us(n);
    for (int i = 0; i < n; ++i) {
        int v = -1, mx = INF;
        for (int j = 0; j < n; ++j) {
            if (!us[j] && nd[j] <= mx) {
                v = j;
                mx = nd[j];
            }
        }
        us[v] = 1;
        for (int in : g[v]) {
            auto [to, c, w] = ed[in];
            if (c == 0) continue;
            nd[to] = min(nd[to], nd[v] + w + d[v] - d[to]);
        }
    }
    for (int i = 0; i < n; ++i) {
        d[i] = nd[i] + d[i];
    }
}

int used[MAX];
int t;

int dfs(int v, int fl) {
    if (v == t) return fl;
    used[v] = 1;
    for (int in : g[v]) {
        auto [to, c, w] = ed[in];
        if (used[to] || c < 1 || d[v] + w != d[to]) continue;
        int x = dfs(to, min(fl, c));
        if (!x) continue;
        upd(in, x);
        return x;
    }
    return 0;
}

pair<int, ll> sl(int n) {
    dist(n);
    ll ans = 0;
    int ansfl = 0;
    while (true) {
        fill(used, used + n, 0);
        int fl = dfs(0, INF);
        if (!fl) break;
        ans += 1ll * fl * d[t];
        ansfl += fl;
        dist(n);
    }
    return {ansfl, ans};
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }
    t = 2 * n + 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int w;
            cin >> w;
            add_ed(i, j + n, INF, w);
        }
        add_ed(0, i, a[i - 1], 0);
        add_ed(i + n, t, a[i - 1], 0);
    }
    auto [fl, ans] = sl(2 * n + 2);
    if (fl < sum || sum % 2 == 1) {
        cout << -1 << endl;
    } else {
        cout << ans / 2 << endl;
    }
    return 0;
}

