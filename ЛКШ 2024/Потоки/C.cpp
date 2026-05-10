#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int v, u, cap, fl, in;
    Edge(int v = 0, int u = 0, int cap = 0, int fl = 0, int in = 0) : v(v), u(u), cap(cap), fl(fl), in(in) {};
};

const int MAX = 1e2, INF = 1e9;
vector<Edge> ed;
vector<int> g[MAX];

void add_ed(int v, int u, int cap) {
    g[v].push_back((int)ed.size());
    ed.push_back(Edge(v, u, cap, 0, (int)ed.size()));
    g[u].push_back((int)ed.size());
    ed.push_back(Edge(u, v, 0, 0, (int)ed.size()));
}

void add_fl(int in, int fl) {
    ed[in].cap -= fl;
    ed[in].fl += fl;
    ed[in ^ 1].cap += fl;
}

int t;
vector<int> used(MAX);
int ans = 0;

int dfs(int v, int can_flow) {
    if (v == t) {
        ans += can_flow;
        return can_flow;
    }
    if (used[v] || can_flow == 0) return 0;
    used[v] = 1;
    for (int ind : g[v]) {
        int fl = dfs(ed[ind].u, min(can_flow, ed[ind].cap));
        add_fl(ind, fl);
        if (fl > 0) return fl;
    }
    return 0;
}

void to_ans(int v) {
    used[v] = 1;
    for (int ind : g[v]) {
        //cout << ind << " " << ed[ind].cap << endl;
        if (!ed[ind].cap || used[ed[ind].u]) continue;
        to_ans(ed[ind].u);
    }
}

signed main() {
    int n;
    cin >> n;
    //vector<vector<char>> f(n, vector<char> (n));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            char c;
            cin >> c;
            if (c - '0') {
                add_ed(i, j, 1);
            }
        }
    }
    int last = 1;
    int now_max = INF;
    for (int _ = 2; _ <= n; ++_) {
        t = _;
        ans = 0;
        for (int i = 1; i <= n; ++i) {
            for (int ind : g[i]) {
                if (ind % 2) {
                    ed[ind].cap = 0;
                    ed[ind].fl = 0;
                } else {
                    ed[ind].cap = 1;
                    ed[ind].fl = 0;
                }
            }
        }
        used.assign(n + 1, 0);
        while (dfs(1, INF)) {
            used.assign(n + 1, 0);
        }
        //cout << "! " << _ << " " << ans << endl;
        if (now_max > ans) {
            last = _;
            now_max = ans;
        }
    }
    //cout << now_max << endl;
    t = last;
    ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int ind : g[i]) {
            if (ind % 2) {
                ed[ind].cap = 0;
                ed[ind].fl = 0;
            } else {
                ed[ind].cap = 1;
                ed[ind].fl = 0;
            }
        }
    }
    used.assign(n + 1, 0);
    while (dfs(1, INF)) {
        used.assign(n + 1, 0);
    }
    used.assign(n + 1, 0);
    to_ans(1);
    for (int i = 1; i <= n; ++i) {
        if (used[i]) {
            cout << i << " ";
        }
    }
    cout << endl;
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            cout << i << " ";
        }
    }
    return 0;
}
