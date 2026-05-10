#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int v, u, cap, fl, in;
    Edge(int v = 0, int u = 0, int cap = 0, int fl = 0, int in = 0) : v(v), u(u), cap(cap), fl(fl), in(in) {};
};

const int MAX = 1e2, INF = 1e9, LN = 30;
vector<Edge> ed;
vector<int> g[MAX];

void add_ed(int v, int u, int cap) {
    g[v].push_back((int)ed.size());
    ed.push_back(Edge(v, u, cap, 0, (int)ed.size()));
    g[u].push_back((int)ed.size());
    ed.push_back(Edge(u, v, 0, 0, (int)ed.size()));
}

void add_fl(int i, int fl) {
    ed[i].cap -= fl;
    ed[i].fl += fl;
    ed[i ^ 1].cap += fl;
}

vector<int> used(MAX, 0);
int t;
int ans = 0;

int dfs(int v, int can_flow, int k) {
    //cout << v << " " << k << " " << can_flow << endl;
    if (v == t) {
        //cout << k << " " << can_flow << endl;
        ans += can_flow;
        return can_flow;
    }
    if (used[v] == 1 || can_flow < (1 << k)) return 0;
    //cout << v << " " << k << endl;
    used[v] = 1;
    for (int ind : g[v]) {
        int fl = dfs(ed[ind].u, min(can_flow, ed[ind].cap), k);
        add_fl(ind, fl);
        if (fl > 0) return fl;
    }
    return 0;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        add_ed(a, b, c);
    }
    t = n - 1;
    for (int k = LN; k >= 0; --k) {
        used.assign(n, 0);
        while (dfs(0, INF, k)) {
            used.assign(n, 0);
        }
    }
    cout << ans << endl;
    return 0;
}
