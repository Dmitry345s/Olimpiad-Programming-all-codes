#include<bits/stdc++.h>

using namespace std;

struct node {
    int ans, al, ar;
    node() {
        ans = 0;
        al = 0;
        ar = 0;
    }
    node(int ans1, int al1, int ar1) {
        ans = ans1;
        al = al1;
        ar = ar1;
    }
};

node operator + (node a, node b) {
    int ch = min(a.ar, b.al);
    node c = node(a.ans + b.ans + 2 * ch, a.al + b.al - ch, b.ar + a.ar - ch);
    return c;
}

int MAX = 1e6;
vector<node> tree(4 * MAX);
string s;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        if (s[l] == '(') {
            tree[v] = node(0, 0, 1);
        } else {
            tree[v] = node(0, 1, 0);
        }
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
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
    cin >> s;
    int n = s.size();
    int q;
    cin >> q;
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << get(1, 0, n, l, r).ans << endl;
    }
    return 0;
}
