#include<bits/stdc++.h>

using namespace std;

int MAXM = 2e5;
vector<int> a(MAXM), tree(4 * MAXM);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        if (a[l] == 0) {
            tree[v] = 1;
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
            tree[v] = 1;
        } else {
            tree[v] = 0;
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

int get(int v, int l, int r, int qr) {
    if (l >= qr) {
        return 0;
    }
    if (r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, qr) + get(2 * v + 1, m, r, qr);
}

int get2(int v, int l, int r, int k) {
    int m = (l + r) / 2;
    if (l + 1 == r) {
        if (tree[v] && k == 1) {
            return l;
        }
        return 1e9;
    }
    if (tree[2 * v] >= k) {
        return get2(2 * v, l, m, k);
    }
    return get2(2 * v + 1, m, r, k - tree[2 * v]);
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
        if (t == 'u') {
            int id, x;
            cin >> id >> x;
            --id;
            update(1, 0, n, id, x);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            k += get(1, 0, n, l);
            int ch = get2(1, 0, n, k) + 1;
            if (ch > r) {
                cout << -1 << " ";
            } else {
                cout << ch << " ";
            }
        }
    }
    return 0;
}
