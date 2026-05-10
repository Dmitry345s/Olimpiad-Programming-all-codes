#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int v, to, cap, fl;
    Edge(int v = 0, int to = 0, int cap = 0, int fl = 0) : v(v), to(to), cap(cap), fl(fl) {}
};

const int MAX = 205, INF = 1e9 + 5, LN = 30;
vector<Edge> ed;
vector<vector<int>> g(MAX);

void add_ed(int v, int u, int cap) {
    g[v].push_back((int)ed.size());
    ed.push_back(Edge(v, u, cap, 0));
    g[u].push_back((int)ed.size());
    ed.push_back(Edge(u, v, 0, 0));
}

void add_fl(int i, int fl) {
    ed[i].cap -= fl;
    ed[i].fl += fl;
    ed[i ^ 1].cap += fl;
}

int t;
int ans = 0;
int timer = 1;
vector<int> used(MAX);

int dfs(int v, int can_flow, int k) {
    if (v == t) {
        ans += can_flow;
        return can_flow;
    }
    if (used[v] == timer || can_flow < (1 << k)) return 0;
    used[v] = timer;
    for (int ind : g[v]) {
        int fl = dfs(ed[ind].to, min(can_flow, ed[ind].cap), k);
        add_fl(ind, fl);
        if (fl > 0) return fl;
    }
    return 0;
}

bool ch(int x, int n, int m, vector<vector<int>> teas, vector<int> a) {
    g.clear();
    g.resize(2 * n + 2 * m + 5);
    ed.clear();
    for (int i = 1; i <= n; ++i) {
        add_ed(0, i, INF);
        add_ed(i, i + n, x);
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (int)teas[i - 1].size(); ++j) {
            add_ed(i + n, teas[i - 1][j] + 2 * n, INF);
        }
    }
    for (int i = 1; i <= m; ++i) {
        add_ed(i + 2 * n, i + 2 * n + m, a[i - 1]);
        add_ed(i + 2 * n + m, 2 * m + 2 * n + 1, INF);
    }
    //cout << 1 << endl;
    ans = 0;
    for (int i = LN; i >= 0; --i) {
        timer++;
        t = 2 * m + 2 * n + 1;
        while (dfs(0, INF, i)) {
            timer++;
        }
    }
    //cout << ans << " " << x << endl;
    return ans == x * n;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> teas(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        teas[i].resize(c);
        for (int j = 0; j < c; ++j) {
            cin >> teas[i][j];
        }
    }
    int l = 0, r = INF;
    while (l + 1 < r) {
        //cout << l << " " << r << endl;
        int c = (l + r) / 2;
        if (ch(c, n, m, teas, a)) {
            l = c;
        } else {
            r = c;
        }
    }
    cout << l << endl;
    return 0;
}
