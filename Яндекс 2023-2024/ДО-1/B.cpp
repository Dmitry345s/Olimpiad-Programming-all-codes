#include<bits/stdc++.h>

using namespace std;

struct node {
    int mx;
    int id;
    node() {
        mx = -2e9;
        id = -1;
    }
    node(int mx1, int id1) {
        mx = mx1;
        id = id1;
    }
};

node operator + (node a, node b) {
    if (a.mx >= b.mx) {
        return a;
    } else {
        return b;
    }
}

int MAXM = 1e5;
vector<node> tree(4 * MAXM);
vector<int> a(MAXM);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = node(a[l], l);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

node get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return node();
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(1, 0, n);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        node ans = get(1, 0, n, l, r);
        cout << ans.id + 1 << '\n';
    }
    return 0;
}
