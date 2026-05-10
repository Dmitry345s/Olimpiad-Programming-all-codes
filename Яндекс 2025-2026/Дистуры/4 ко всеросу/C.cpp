#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;

int tree[4 * MAX];

void update(int v, int l, int r, int in, int x) {
    if (l + 1 == r) {
        tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x);
    } else {
        update(2 * v + 1, m, r, in, x);
    }
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

int get1(int v, int l, int r, int ql, int qr, int s) {
    if (ql == qr) return ql + 1;
    if (qr <= l || r <= ql) return MAX;
    if (l + 1 == r) {
        if (tree[v] >= s) return MAX;
        return l;
    }
    int m = (l + r) / 2;
    if (ql <= l && r <= qr) {
        if (tree[v] >= s) return MAX;
        if (tree[2 * v] < s) {
            return get1(2 * v, l, m, ql, qr, s);
        }
        return get1(2 * v + 1, m, r, ql, qr, s);
    }
    return min(get1(2 * v, l, m, ql, qr, s), get1(2 * v + 1, m, r, ql, qr, s));
}

int get0(int v, int l, int r, int ql, int qr, int s) {
    if (ql == qr) return ql - 1;
    if (qr <= l || r <= ql) return -1;
    if (l + 1 == r) {
        if (tree[v] >= s) return -1;
        return l;
    }
    int m = (l + r) / 2;
    if (ql <= l && r <= qr) {
        if (tree[v] >= s) return -1;
        if (tree[2 * v + 1] < s) {
            return get0(2 * v + 1, m, r, ql, qr, s);
        }
        return get0(2 * v, l, m, ql, qr, s);
    }
    return max(get0(2 * v, l, m, ql, qr, s), get0(2 * v + 1, m, r, ql, qr, s));
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        update(1, 0, m, i, w);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int t, b, s;
        cin >> t >> b >> s;
        --b;
        if (t == 1) {
            update(1, 0, m, b, s);
        } else {
            int rr = min(n - 1, get1(1, 0, m, b, m, s));
            int ll = get0(1, 0, m, 0, b, s);
            cout << min(n, rr - ll) << endl;
        }
    }
    return 0;
}
