#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5;
vector<vector<int>> g(MAX);
vector<int> a(MAX);
vector<int> tin(MAX), tout(MAX), sz(MAX), ord, head(MAX), ps(MAX);
int timer = 0;

void dfs(int v, int p) {
    sz[v] = 1;
    ps[v] = p;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
    }
}

bool cmp(int a, int b) {
    if (a == b) {
        return a < b;
    }
    return sz[a] > sz[b];
}

void dfs2(int v, int p, int now) {
    tin[v] = timer++;
    head[v] = now;
    ord.push_back(v);
    sort(g[v].begin(), g[v].end(), cmp);
    int flag = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        if (!flag) {
            dfs2(to, v, now);
            flag = 1;
        } else {
            dfs2(to, v, to);
        }
    }
    tout[v] = timer;
}

vector<int> tree(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = a[ord[l]];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void update(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x);
    } else {
        update(2 * v + 1, m, r, in, x);
    }
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    //cout << v << " " << l << " " << r << " " << tree[v] << endl;
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

bool pr(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int get_ans(int v, int u, int n) {
    int ans = 0;
    for (int i = 0; i < 2; ++i) {
        while (!pr(head[v], u)) {
            ans = max(ans, get(1, 0, n, tin[head[v]], tin[v] + 1));
            //cout << head[v] << " " << u << " " << ans << endl;
            v = head[v];
            v = ps[v];
        }
        swap(u, v);
    }
    //cout << tin[u] << " " << tin[v] << endl;
    return max(ans, get(1, 0, n, min(tin[u], tin[v]), max(tin[u], tin[v]) + 1));
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0);
    dfs2(0, 0, 0);
    build(1, 0, n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '!') {
            int v, h;
            cin >> v >> h;
            --v;
            //cout << tin[v] << endl;
            update(1, 0, n, tin[v], h);
        } else {
            int v, u;
            cin >> v >> u;
            --v; --u;
            cout << get_ans(v, u, n) << endl;
        }
    }
    return 0;
}
