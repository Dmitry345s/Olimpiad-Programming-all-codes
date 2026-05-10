#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5 + 5;
vector<int> a(MAX), tree(4 * MAX);

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

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x);
    } else {
        update(2 * v + 1, m, r, id, x);
    }
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr, int k) {
    if (qr <= l || r <= ql) {
        return -2;
    }
    int m = (l + r) / 2;
    if (ql <= l && r <= qr) {
        if (tree[v] >= k) {
            if (l + 1 == r) {
                return l;
            }
            if (tree[2 * v] >= k) {
                return get(2 * v, l, m, ql, qr, k);
            }
            return get(2 * v + 1, m, r, ql, qr, k);
        }
        return -2;
    }
    int ans1 = get(2 * v, l, m, ql, qr, k);
    if (ans1 != -2) {
        return ans1;
    }
    return get(2 * v + 1, m, r, ql, qr, k);
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(1, 0, n);
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 0) {
            int j, x;
            cin >> j >> x;
            --j;
            update(1, 0, n, j, x);
        } else {
            int j, x;
            cin >> j >> x;
            --j;
            cout << get(1, 0, n, j, n, x) + 1 << endl;
        }
    }
}
