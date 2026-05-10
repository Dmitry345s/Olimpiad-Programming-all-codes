#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int v, u, cap, fl;
    Edge(int v = 0, int u = 0, int cap = 0, int fl = 0) : v(v), u(u), cap(cap), fl(fl) {}
};

const int MAX = 1e5, INF = 1e9;
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

int t;
int anss = 0;
vector<int> used(MAX, 0);

int dfs(int v, int can_flow) {
    if (v == t) {
        anss += can_flow;
        return can_flow;
    }
    if (used[v] == 1 || can_flow == 0) return 0;
    used[v] = 1;
    for (int ind : g[v]) {
        int fl = dfs(ed[ind].u, min(can_flow, ed[ind].cap));
        add_fl(ind, fl);
        if (fl > 0) return fl;
    }
    return 0;
}

vector<int> ans;

int to_ans(int v) {
    used[v] = 1;
    if (v == t) return 1;
    for (int ind : g[v]) {
        int to = ed[ind].u;
        if (used[to] || (ed[ind].fl ^ ed[ind ^ 1].fl) == 0) continue;
        int flag = to_ans(to);
        if (flag) {
            ed[ind].fl = 0;
            ans.push_back(to);
            return 1;
        }
    }
    return 0;
}

signed main() {
    int n, m, a;
    cin >> n >> m >> a >> t;
    --a; --t;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        add_ed(u, v, 1);
    }
    used.assign(n, 0);
    dfs(a, INF);
    //cout << anss << endl;
    used.assign(n, 0);
    dfs(a, INF);
    if (anss != 2) {
        cout << "NO" << endl;
        return 0;
    }
    cout << "YES" << endl;
    used.assign(n, 0);
    if (!to_ans(a)) return 0;
    ans.push_back(a);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    ans.clear();
    used.assign(n, 0);
    if (!to_ans(a)) return 0;
    ans.push_back(a);
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
/*6 8 1 6
1 2
2 3
3 4
4 5
5 2
4 6
1 4
2 6*/
