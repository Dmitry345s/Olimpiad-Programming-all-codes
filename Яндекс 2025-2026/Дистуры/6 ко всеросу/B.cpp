#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

#define int long long

using namespace std;

const int MAX = 3e5 + 5, LN = 19;
vector<int> g[MAX];
int cha[MAX], chb[MAX];
int a[MAX], b[MAX];
int n;

int tree[2][4 * MAX];

void update(int v, int l, int r, int in, int x, int u) {
    if (l + 1 == r) {
        tree[u][v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x, u);
    } else {
        update(2 * v + 1, m, r, in, x, u);
    }
    tree[u][v] = tree[u][2 * v] + tree[u][2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr, int u) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return tree[u][v];
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr, u) + get(2 * v + 1, m, r, ql, qr, u);
}

int fn(int v, int l, int r, int ql, int qr, int u) {
    if (qr <= l || r <= ql) return MAX;
    if (tree[u][v] == 0) return MAX;
    if (l + 1 == r) return l;
    int m = (l + r) / 2;
    if (ql <= l && r <= qr) {
        if (tree[u][2 * v] > 0) {
            return fn(2 * v, l, m, ql, qr, u);
        }
        return fn(2 * v + 1, m, r, ql, qr, u);
    }
    int y = fn(2 * v, l, m, ql, qr, u);
    if (y == MAX) {
        return fn(2 * v + 1, m, r, ql, qr, u);
    }
    return y;
}

int timer = 0;
int sz[MAX];
int up[MAX][LN];
int tin[MAX], tout[MAX];
vector<int> ord;
int h[MAX];

void dfs(int v, int p) {
    sz[v] = 1;
    tin[v] = timer++;
    h[v] = h[p] + 1;
    ord.push_back(v);
    if (cha[v] != -1) {
        update(1, 0, n, tin[v], 1, 0);
    }
    if (chb[v] != -1) {
        update(1, 0, n, tin[v], 1, 1);
    }
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
    tout[v] = timer;
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

int dist(int a, int b) {
    return h[a] + h[b] - 2 * h[lca(a, b)];
}

vector<int> ans;

void solve(int v, int tp) {
    int sum = get(1, 0, n, tin[v], tin[v] + sz[v], tp);
    if (sum == 0) {
        for (int i = LN - 1; i >= 0; --i) {
            int now = up[v][i];
            int sumn = get(1, 0, n, tin[now], tin[now] + sz[now], tp);
            if (sumn == 0) {
                v = up[v][i];
            }
        }
        v = up[v][0];
    }
    if (get(1, 0, n, tin[v], tin[v] + sz[v], tp) == 0) return;
    int y = fn(1, 0, n, tin[v], tin[v] + sz[v], tp);
    int v2 = ord[y];
    if (tp == 0) {
        ans.push_back(cha[v2]);
        update(1, 0, n, tin[v2], 0, 0);
    } else {
        ans.push_back(chb[v2]);
        update(1, 0, n, tin[v2], 0, 1);
    }
    solve(v2, tp ^ 1);
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int m;
    cin >> n >> m;
    fill(cha, cha + n, -1);
    fill(chb, chb + n, -1);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
        --a[i];
        cha[a[i]] = i;
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        --b[i];
        chb[b[i]] = i;
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0);
    solve(0, 0);
    vector<int> ver;
    ver.push_back(0);
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i % 2) {
            ver.push_back(b[ans[i]]);
        } else {
            ver.push_back(a[ans[i]]);
        }
    }
    ver.push_back(0);
    int cnt = 0;
    for (int i = 0; i < (int)ver.size() - 1; ++i) {
        cnt += dist(ver[i], ver[i + 1]);
    }
    cout << cnt << endl;
    for (int v : ans) {
        cout << v + 1 << " ";
    }
    cout << endl;
    return 0;
}
