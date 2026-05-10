#include<bits/stdc++.h>

using namespace std;

struct node {
    int ans, fl, fr, sz;
    node() {
        ans = 0;
        fl = 0;
        fr = 0;
        sz = 0;
    }
    node(int ans1, int fl1, int fr1, int sz1) {
        ans = ans1;
        fl = fl1;
        fr = fr1;
        sz = sz1;
    }
};

node operator + (node a, node b) {
    node ans = node(max(a.fr + b.fl, max(a.ans, b.ans)), a.fl, b.fr, a.sz + b.sz);
    if (a.fl == a.sz) {
        ans.fl += b.fl;
    }
    if (b.fr == b.sz) {
        ans.fr += a.fr;
    }
    return ans;
}

int MAXM = 5e5;
vector<node> tree(4 * MAXM);
vector<int> a(MAXM);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        if (a[l] == 0) {
            tree[v] = node(1, 1, 1, 1);
        } else {
            tree[v] = node(0, 0, 0, 1);
        }
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        if (x == 0) {
            tree[v] = node(1, 1, 1, 1);
        } else {
            tree[v] = node(0, 0, 0, 1);
        }
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x);
    } else {
        update(2 * v + 1, m, r, id, x);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

node get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return node();
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
    build(1, 0, n);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        string t;
        cin >> t;
        if (t == "QUERY") {
            int l, r;
            cin >> l >> r;
            --l;
            cout << get(1, 0, n, l, r).ans << endl;
        } else {
            int id, x;
            cin >> id >> x;
            --id;
            update(1, 0, n, id, x);
        }
    }
    return 0;
}
