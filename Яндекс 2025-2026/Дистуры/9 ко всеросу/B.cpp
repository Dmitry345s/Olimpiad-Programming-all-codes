#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 3e5 + 1, LN = 19;
int up[MAX][LN];
vector<int> g[MAX];
int h[MAX];
int tin[MAX];
int tout[MAX];
int timer = 0;

void dfs(int v, int p) {
    h[v] = h[p] + 1;
    up[v][0] = p;
    tin[v] = timer++;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer++;
}

int ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    if (ch(b, a)) return b;
    for (int i = LN - 1; i >= 0; --i) {
        if (!ch(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

int ps[2 * MAX];
int hg[2 * MAX];

int root(int v) {
    if (ps[v] == v) return v;
    return ps[v] = root(ps[v]);
}

void unite(int v, int u) {
    v = root(v);
    u = root(u);
    if (u == v) return;
    ps[v] = u;
    hg[u] = min(hg[u], hg[v]);
}

vector<int> sts[MAX];
int cnt_em = 0;
int y[MAX];
const int MOD = 1e9 + 7;

void solve(int v, int p) {
    for (int to : g[v]) {
        if (to == p) continue;
        solve(to, v);
        if (y[to] != -1 && hg[root(y[to])] < h[v]) {
            sts[v].push_back(y[to]);
        }
    }
    if (v == 0) return;
    if (sts[v].empty()) {
        cnt_em++;
        y[v] = -1;
        return;
    }
    y[v] = sts[v][0];
    for (int i = 1; i < (int)sts[v].size(); ++i) {
        unite(y[v], sts[v][i]);
    }
    sts[v].clear();
}

vector<int> g2[2 * MAX];
int used[2 * MAX];
int fl = 1;

void tr(int v, int num) {
    used[v] = num;
    for (int to : g2[v]) {
        if (used[to]) {
            if (used[to] == num) {
                fl = 0;
            }
            continue;
        }
        tr(to, num % 2 + 1);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int rt = 0;
    dfs(rt, rt);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        assert(a != b);
        if (a == b) {
            ps[2 * i] = -1;
            ps[2 * i + 1] = -1;
            continue;
        }
        int x = lca(a, b);
        if (a != x) {
            sts[a].push_back(2 * i);
        }
        if (b != x) {
            sts[b].push_back(2 * i + 1);
        }
        ps[2 * i] = 2 * i;
        hg[2 * i] = h[x];
        ps[2 * i + 1] = 2 * i + 1;
        hg[2 * i + 1] = h[x];
    }
    solve(rt, rt);
    for (int i = 0; i < m; ++i) {
        if (ps[2 * i] == -1) continue;
        int a = root(ps[2 * i]);
        int b = root(ps[2 * i + 1]);
        g2[a].push_back(b);
        g2[b].push_back(a);
    }
    int cnt = 0;
    for (int i = 0; i < 2 * m; ++i) {
        if ((int)g2[i].size() > 0 && !used[i]) {
            cnt++;
            tr(i, 1);
        }
    }
    int ans = fl;
    for (int k = 0; k < cnt + cnt_em; ++k) {
        ans = (ans * 2) % MOD;
    }
    cout << ans << endl;
    return 0;
}
