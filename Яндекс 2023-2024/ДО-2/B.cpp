#include<bits/stdc++.h>

using namespace std;

struct node {
    long long al, ar, an, sz;
    node() {
        al = 0;
        ar = 0;
        an = 0;
        sz = 0;
    }
    node(int ch, int sz1) {
        sz = sz1;
        al = ch;
        ar = ch;
        an = ch;
    }
};

node operator + (node a, node b) {
    node c = node(0, 0);
    c.sz = a.sz + b.sz;
    c.an = max(max(a.an, b.an), a.ar + b.al);
    c.al = a.al;
    if (a.al == a.sz) {
        c.al += b.al;
    }
    c.ar = b.ar;
    if (b.ar == b.sz) {
        c.ar += a.ar;
    }
    return c;
}

int MAX = 2e5;
vector<long long> a(MAX), b(MAX);
vector<node> tree(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = node((b[l] == 1), 1);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int id, long long d) {
    if (l + 1 == r) {
        b[l] += d;
        tree[v] = node((b[l] == 1), 1);
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, d);
    } else {
        update(2 * v + 1, m, r, id, d);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

node get(int v, int l, int r, int ql, int qr) {
    if (ql == qr) {
        return node();
    }
    if (qr <= l || r <= ql) {
        return node(0, 0);
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        b[i] = a[i + 1] - a[i];
    }
    if (n == 1) {
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            char t;
            cin >> t;
            if (t == '?') {
                int l, r;
                cin >> l >> r;
                cout << 1 << endl;
            } else {
                int l, r, d;
                cin >> l >> r >> d;
            }
        }
        return 0;
    }
    build(1, 0, n - 1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == '?') {
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << get(1, 0, n - 1, l, r).an + 1 << endl;
        } else {
            int l, r, d;
            cin >> l >> r >> d;
            --l; --r;
            if (l != 0) {
                update(1, 0, n - 1, l - 1, d);
            }
            if (r != n - 1) {
                update(1, 0, n - 1, r, -d);
            }
        }
    }
    return 0;
}
