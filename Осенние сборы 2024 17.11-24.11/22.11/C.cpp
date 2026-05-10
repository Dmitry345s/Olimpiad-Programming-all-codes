#include<bits/stdc++.h>

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long

using namespace std;

const int MAX = 3e5, LN = 19, INF = 2e9;
vector<pair<int, int>> g[MAX];
int up[LN][MAX];
vector<int> ord;
int tin[MAX];
int tout[MAX];
int sz[MAX];
int timer = 0;
int te[MAX];
int tp[MAX];
int np[MAX];


void dfs(int v, int p) {
    sz[v] = 1;
    for (auto [to, in] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
        te[to] = in;
    }
}

void dfs2(int v, int p, int num) {
    up[0][v] = p;
    for (int i = 1; i < LN; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    tin[v] = timer++;
    ord.push_back(v);
    int flag = 1;
    int now = num;
    if (now == -1) {
        now = v;
    }
    np[v] = now;
    for (auto [to, in] : g[v]) {
        if (to == p) continue;
        if (flag) {
            dfs2(to, v, now);
            flag = 0;
        } else {
            dfs2(to, v, -1);
        }
    }
    tout[v] = timer;
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (sz[a.first] == sz[b.first]) {
        return a.second < b.second;
    }
    return sz[a.first] > sz[b.first];
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    if (ch(b, a)) return b;
    for (int i = LN - 1; i >= 0; --i) {
        if (!ch(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

int tree[4 * MAX];

void update(int l, int r, int x, int n) {
    //cout << ql << " " << qr << " " << x << endl;
    l += n; r += n;
    while (l < r) {
        if (l & 1) {
            tree[l] = min(tree[l], x);
            l++;
        }
        if (r & 1) {
            r--;
            tree[r] = min(tree[r], x);
        }
        l /= 2;
        r /= 2;
    }
}

int fsqa[MAX];

void forsq(int a, int x, int l, int n) {
    //if (a == x) return;
    while (true) {
        if (a == x) return;
        if (ch(np[a], x)) {
            update(tin[x] + 1, tin[a] + 1, l, n);
            return;
        } else {
            update(tin[np[a]], tin[a] + 1, l, n);
            a = np[a];
            a = up[0][a];
        }
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
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    dfs(0, 0);
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end(), cmp);
    }
    dfs2(0, 0, -1);
    fill(fsqa, fsqa + n, INF);
    fill(tree, tree + 2 * n, INF);
    for (int i = 0; i < m; ++i) {
        int u, v, l;
        cin >> u >> v >> l;
        --u; --v;
        int x = lca(u, v);
        //cout << x << endl;
        forsq(u, x, l, n);
        forsq(v, x, l, n);
    }
    for (int i = 0; i < n; ++i) {
        int v = i + n;
        while (v) {
            fsqa[ord[i]] = min(tree[v], fsqa[ord[i]]);
            v /= 2;
        }
    }
    vector<int> ans(n - 1);
    for (int i = 1; i < n; ++i) {
        ans[te[i]] = fsqa[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        if (ans[i] == INF) {
            cout << -1 << '\n';
            continue;
        }
        cout << ans[i] << '\n';
    }
    return 0;
}
