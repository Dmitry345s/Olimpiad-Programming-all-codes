#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5 + 2;
vector<long long> tree(4 * MAX);

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] += x;
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

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        update(1, 0, n, i, a);
        if (i != n - 1) {
            update(1, 0, n, i + 1, -a);
        }
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == 'a') {
            int l, r, add;
            cin >> l >> r >> add;
            --l;
            update(1, 0, n, l, add);
            if (r != n) {
                update(1, 0, n, r, -add);
            }
        } else {
            int id;
            cin >> id;
            cout << get(1, 0, n, 0, id) << endl;
        }
    }
    return 0;
}
