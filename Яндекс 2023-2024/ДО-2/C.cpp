#include<bits/stdc++.h>

using namespace std;

struct node{
    long long ans;
    int g[20];
    int sz;
    node() {
        ans = 0;
        sz = 0;
    }
    node(int a) {
        ans = a;
        for (int i = 0; i < 20; ++i) {
            g[i] = (a >> i) & 1;
        }
        sz = 1;
    }
};

node operator + (node a, node b) {
    node c;
    c.ans = a.ans + b.ans;
    for (int i = 0; i < 20; ++i) {
        c.g[i] = a.g[i] + b.g[i];
    }
    c.sz = a.sz + b.sz;
    return c;
}

int MAX = 1e5;
vector<int> a(MAX), update_tree(4 * MAX);
vector<node> tree(4 * MAX);

void push(int v) {
    int x = update_tree[v];
    long long ans1 = 0, ans2 = 0;
    for (int i = 0; i < 20; ++i) {
        if ((x >> i) & 1) {
            tree[2 * v].g[i] = tree[2 * v].sz - tree[2 * v].g[i];
            tree[2 * v + 1].g[i] = tree[2 * v + 1].sz - tree[2 * v + 1].g[i];
        }
        ans1 += 1ll * (1 << i) * tree[2 * v].g[i];
        ans2 += 1ll * (1 << i) * tree[2 * v + 1].g[i];
    }
    tree[2 * v].ans = ans1;
    tree[2 * v + 1].ans = ans2;
    update_tree[2 * v] = (update_tree[2 * v] ^ update_tree[v]);
    update_tree[2 * v + 1] = (update_tree[2 * v + 1] ^ update_tree[v]);
    update_tree[v] = 0;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = node(a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int ql, int qr, int d) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        long long ans = 0;
        for (int i = 0; i < 20; ++i) {
            if ((d >> i) & 1) {
                tree[v].g[i] = tree[v].sz - tree[v].g[i];
            }
            ans += tree[v].g[i] * (1 << i);
        }
        tree[v].ans = ans;
        update_tree[v] = (update_tree[v] ^ d);
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update(2 * v, l, m, ql, qr, d);
    update(2 * v + 1, m, r, ql, qr, d);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

node get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return node();
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    push(v);
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(1, 0, n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            --l;
            cout << get(1, 0, n, l, r).ans << endl;
        } else {
            int l, r, d;
            cin >> l >> r >> d;
            --l;
            update(1, 0, n, l, r, d);
        }
    }
    return 0;
}
