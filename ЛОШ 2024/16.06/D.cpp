#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<int> tree(4 * MAX);

void build(int v, int l, int r, vector<int> & st) {
    if (l + 1 == r) {
        tree[v] = st[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, st);
    build(2 * v + 1, m, r, st);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
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
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr) {
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
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    string s, t;
    cin >> s >> t;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        a[i] = s[i] - '0';
        b[i] = t[i] - '0';
    }
    vector<int> a2 = a, b2 = b;
    for (int i = 1; i < n - 1; ++i) {
        if (a[i - 1] == a[i + 1] && a[i - 1] == 0) {
            b2[i] = 1;
        }
    }
    for (int i = 1; i < n - 1; ++i) {
        if (b2[i - 1] == b2[i + 1] && b2[i - 1] == 1) {
            a2[i] = 1;
        }
    }
    build(1, 0, n, a2);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        if (l + 2 == r) {
            update(1, 0, n, l, a[l]);
            update(1, 0, n, r, a[r]);
            update(1, 0, n, l + 1, (a[l + 1] | (b[l] == b[r] && b[l] == 1)));
            cout << get(1, 0, n, l, r + 1) << endl;
            update(1, 0, n, l, a2[l]);
            update(1, 0, n, r, a2[r]);
            update(1, 0, n, l + 1, a2[l + 1]);
            continue;
        }
        if (r - 1 > 0) {
            int now = a[r - 1];
            if (b2[r - 2] == b[r] && b[r] == 1) {
                now = 1;
            }
            update(1, 0, n, r - 1, now);
        }
        if (l + 1 < n - 1) {
            int now = a[l + 1];
            if (b2[l + 2] == b[l] && b[l] == 1) {
                now = 1;
            }
            update(1, 0, n, l + 1, now);
        }
        update(1, 0, n, r, a[r]);
        update(1, 0, n, l, a[l]);
        cout << get(1, 0, n, l, r + 1) << endl;
        update(1, 0, n, r, a2[r]);
        update(1, 0, n, l, a2[l]);
        if (r - 1 > 0) {
            update(1, 0, n, r - 1, a2[r - 1]);
        }
        if (l + 1 < n - 1) {
            update(1, 0, n, l + 1, a2[l + 1]);
        }
    }
    return 0;
}
