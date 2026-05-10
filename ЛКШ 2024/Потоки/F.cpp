#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int v, to, cap, fl;
    Edge(int v = 0, int to = 0, int cap = 0, int fl = 0) : v(v), to(to), cap(cap), fl(fl) {}
};

const int MAX = 205, INF = 3e5;
vector<Edge> ed;
vector<int> g[MAX];

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

vector<int> used(MAX);
int t;
int ans = 0;
int timer = 1;

int dfs(int v, int can_flow) {
    //cout << "! " << v << " " << can_flow << endl;
    if (v == t) {
        ans += can_flow;
        return can_flow;
    }
    if (used[v] == timer || can_flow == 0) return 0;
    used[v] = timer;
    for (int ind : g[v]) {
        int fl = dfs(ed[ind].to, min(can_flow, ed[ind].cap));
        add_fl(ind, fl);
        if (fl > 0) return fl;
    }
    return 0;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int fans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] < 0) {
            add_ed(0, i + 1, -a[i]);
            //cout << 0 << " " << i + 1 << " " << -a[i] << endl;
        } else if (a[i] > 0) {
            fans += a[i];
            add_ed(i + 1, n + 1, a[i]);
            //cout << i + 1 << " " << n + 1 << " " << a[i] << endl;
        }
    }
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int v;
            cin >> v;
            add_ed(v, i + 1, INF);
            //cout << v << " " << i + 1 << " " << INF << endl;
        }
    }
    t = n + 1;
    while (dfs(0, INF)) {
        timer++;
    }
    //cout << ans << endl;
    cout << max(0, fans - ans) << endl;
    return 0;
}
/*
5
-1 -1 -1 2 2
1 4
3 1 3 5
2 2 4
1 1
1 1*/
