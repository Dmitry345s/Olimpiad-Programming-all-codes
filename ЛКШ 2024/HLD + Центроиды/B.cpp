#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5;
vector<vector<int>> g(MAX);
vector<int> sz(MAX), ps(MAX);

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
    if (sz[a] == sz[b]) {
        return a < b;
    }
    return sz[a] > sz[b];
}

vector<int> head(MAX);
vector<int> ord;
vector<int> tin(MAX), tout(MAX), st(MAX);
int timer = 0;

void dfs2(int v, int p, int now) {
    sort(g[v].begin(), g[v].end(), cmp);
    int mx = 0;
    for (int i = (v != 0); i < (int)g[v].size(); ++i) {
        mx = max(mx, sz[g[v][i]]);
    }
    //cout << v << " " << mx << endl;
    tin[v] = timer++;
    head[v] = now;
    st[v] = (int)ord.size();
    ord.push_back(v);
    int flag = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        if (sz[to] == mx && !flag) {
            dfs2(to, v, now);
            flag = 1;
        } else {
            dfs2(to, v, to);
        }
    }
    tout[v] = timer++;
}

vector<long long> tree(4 * MAX);
vector<long long> a(MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = a[ord[l]];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int in, long long x) {
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
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

long long get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

bool pr(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

long long get_ans(int v, int u, int n) {
    long long ans = 0;
    for (int i = 0; i < 2; ++i) {
        while (!pr(head[v], u)) {
            ans += get(1, 0, n, st[head[v]], st[v] + 1);
            //cout << head[v] << " " << u << " " << ans << endl;
            v = head[v];
            v = ps[v];
        }
        swap(u, v);
    }
    //cout << v << " " << u << endl;
    return ans + get(1, 0, n, min(st[v], st[u]), max(st[v], st[u]) + 1);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, 0);
    //cout << 1 << endl;
    dfs2(0, 0, 0);
    //cout << 1 << endl;
    build(1, 0, n);
    //cout << 1 << endl;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '!') {
            int v, x_new;
            cin >> v >> x_new;
            --v;
            update(1, 0, n, st[v], x_new);
        } else {
            int v, u;
            cin >> v >> u;
            --v; --u;
            cout << get_ans(v, u, n) << endl;
        }
    }
    return 0;
}

/*8
1 2 3 4 5 6 7 8
1 2
2 3
2 4
1 5
5 6
5 7
7 8
100
? 3 8*/
