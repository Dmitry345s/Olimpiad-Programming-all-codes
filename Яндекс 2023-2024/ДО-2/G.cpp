#include<bits/stdc++.h>

using namespace std;

using ull = unsigned long long;

struct node {
    ull h;
    int sz, p;
    node(int h = 0, int sz = 0, int p = 0): h(h), sz(sz), p(p) {}
};

int MAX = 1e5;
vector<ull> pows(MAX), pows2(MAX);
int b = 137;

node operator + (node a, node b) {
    node c;
    c.sz = a.sz + b.sz;
    c.p = 0;
    c.h = a.h * pows[b.sz] + b.h;
    return c;
}

vector<node> tree(4 * MAX);
vector<int> a(MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = node(a[l], r - l);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void push(int v) {
    if (tree[v].p == 0) return;
    tree[2 * v].p = tree[v].p;
    tree[2 * v + 1].p = tree[v].p;
    tree[2 * v].h = tree[v].p * pows2[tree[2 * v].sz - 1];
    tree[2 * v + 1].h = tree[v].p * pows2[tree[2 * v + 1].sz - 1];
    tree[v].p = 0;
}

void update(int v, int l, int r, int ql, int qr, int d) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v].p = d;
        tree[v].h = d * pows2[tree[v].sz - 1];
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
    pows[0] = 1;
    pows2[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        pows[i] = pows[i - 1] * b;
        pows2[i] = pows2[i - 1] + pows[i];
    }
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(1, 0, n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int q;
        cin >> q;
        if (q) {
            int l1, l2, k;
            cin >> l1 >> l2 >> k;
            --l1; --l2;
            if (get(1, 0, n, l1, l1 + k).h == get(1, 0, n, l2, l2 + k).h) {
                cout << '+';
            } else {
                cout << '-';
            }
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            update(1, 0, n, l, r, k);
        }
    }
    return 0;
}
