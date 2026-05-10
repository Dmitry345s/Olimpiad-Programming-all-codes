#include<bits/stdc++.h>

using namespace std;

long long mod = 1e9 + 7;
int b = 179;

struct node {
    int h1, h2, lenf, lenc;
    node() {
        h1 = 0;
        h2 = 0;
        lenf = 0;
        lenc = 0;
    }
    node(int h11, int h21, int lenf1, int lenc1) {
        h1 = h11;
        h2 = h21;
        lenf = lenf1;
        lenc = lenc1;
    }
};

int MAX = 2e5;
vector<long long> pows(MAX);
vector<node> tree(4 * MAX);
string s;

node operator + (node a, node b) {
    if (a.lenc == 0) {
        return b;
    } else if (b.lenc == 0) {
        return a;
    }
    node c;
    c.h2 = (a.h2 * pows[b.lenf]) % mod + b.h2;
    c.h2 %= mod;
    c.lenf = a.lenf + b.lenf;
    if (a.h1 == b.h1) {
        c.h1 = a.h1;
        c.lenc = a.lenc;
    } else if (a.h2 == b.h2) {
        c.h1 = a.h2;
        c.lenc = a.lenf;
    } else {
        c.h1 = c.h2;
        c.lenc = c.lenf;
    }
    return c;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = node((int)s[l] - 97 + 1, (int)s[l] - 97 + 1, 1, 1);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void update(int v, int l, int r, int id, char c) {
    if (l + 1 == r) {
        tree[v] = {(int)c - 97 + 1, (int)c - 97 + 1, 1, 1};
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, c);
    } else {
        update(2 * v + 1, m, r, id, c);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

node get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return node();
    }
    if (ql <= l && r <= qr) {
        cout << v << " " << tree[v].h1 << " " << tree[v].h2 << endl;
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int n;
    cin >> n;
    cin >> s;
    pows[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        pows[i] = (pows[i - 1] * b) % mod;
    }
    build(1, 0, n);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int j;
            char c;
            cin >> j >> c;
            --j;
            update(1, 0, n, j, c);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            cout << get(1, 0, n, l, r).lenc << endl;
        }
    }
    return 0;
}
