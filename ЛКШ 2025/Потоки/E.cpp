#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5, INF = 2e9, LN = 30;

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

vector<int> ans;
int st;

void fin(int v) {
    ans.push_back(v);
    used[v] = 1;
    for (int in : g[v]) {
        if (in % 2 == 0 && ed[in].c == 0) {
            ed[in].c = 1;
            fin(ed[in].v);
            if (v != st) {
                break;
            } else {
                ans.push_back(v);
            }
        }
    }
}

signed main() {
    int n, m, a, h;
    cin >> n >> m >> a >> h;
    --a; --h;
    for (int i = 0; i < m; ++i) {
        int v, u;
        cin >> v >> u;
        --v; --u;
        add(v, u, 1);
    }
    t = h;
    int rans = 0;
    while (true) {
        fill(used, used + n, 0);
        int fl = dfs(a, 1, 0);
        rans += fl;
        if (fl == 0 || rans == 2) break;
    }
    if (rans != 2) {
        cout << "NO" << endl;
        return 0;
    }
    st = a;
    fin(a);
    cout << "YES";
    for (int i = 0; i < (int)ans.size() - 1; ++i) {
        if (ans[i] == a) {
            cout << endl;
        }
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
