#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<long long> tree(4 * MAX), update_tree(4 * MAX), a(MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void push(int v) {
    tree[2 * v] += update_tree[v];
    tree[2 * v + 1] += update_tree[v];
    update_tree[2 * v] += update_tree[v];
    update_tree[2 * v + 1] += update_tree[v];
    update_tree[v] = 0;
}

void update(int v, int l, int r, int ql, int qr, int d) {
    if (r <= ql || qr <= l) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] += d;
        update_tree[v] += d;
        return;
    }
    push(v);
    int m = (l + r) / 2;
    update(2 * v, l, m, ql, qr, d);
    update(2 * v + 1, m, r, ql, qr, d);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

long long INF = 1e18;

long long get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return -INF;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    push(v);
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
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
        char t;
        cin >> t;
        if (t == 'a') {
            int l, r, d;
            cin >> l >> r >> d;
            --l;
            update(1, 0, n, l, r, d);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            cout << get(1, 0, n, l, r) << " ";
        }
    }
    return 0;
}
