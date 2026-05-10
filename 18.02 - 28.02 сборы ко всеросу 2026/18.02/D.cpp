#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

using namespace std;


const int MAX = 5e5 + 10;

int tree[4 * MAX];
int upd_tree[4 * MAX];
int tree2[4 * MAX];
int upd_tree2[4 * MAX];
pair<int, int> stc[MAX];

void build(int v, int l, int r) {
    upd_tree[v] = -1;
    if (l + 1 == r) {
        tree[v] = stc[l].first;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void build2(int v, int l, int r) {
    upd_tree2[v] = -1;
    if (l + 1 == r) {
        tree2[v] = stc[l].second;
        return;
    }
    int m = (l + r) / 2;
    build2(2 * v, l, m);
    build2(2 * v + 1, m, r);
    tree2[v] = min(tree2[2 * v], tree2[2 * v + 1]);
}

void push(int v) {
    int x = upd_tree[v];
    if (x == -1) return;
    upd_tree[2 * v] = x;
    tree[2 * v] = x;
    upd_tree[2 * v + 1] = x;
    tree[2 * v + 1] = x;
    upd_tree[v] = -1;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        tree[v] = x;
        upd_tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void push2(int v) {
    int x = upd_tree2[v];
    if (x == -1) return;
    upd_tree2[2 * v] = x;
    tree2[2 * v] = x;
    upd_tree2[2 * v + 1] = x;
    tree2[2 * v + 1] = x;
    upd_tree2[v] = -1;
}

void update2(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        tree2[v] = x;
        upd_tree2[v] = x;
        return;
    }
    int m = (l + r) / 2;
    push2(v);
    update2(2 * v, l, m, ql, qr, x);
    update2(2 * v + 1, m, r, ql, qr, x);
    tree2[v] = min(tree2[2 * v], tree2[2 * v + 1]);
}

int f2(int v, int l, int r, int q) {
    //cout << v << " " << tree2[v] << " " << l << " " << r << " " << q << endl;
    if (l + 1 == r) {
        if (tree2[v] <= q) return l;
        return r;
    }
    int m = (l + r) / 2;
    push2(v);
    if (tree2[2 * v] <= q) return f2(2 * v, l, m, q);
    return f2(2 * v + 1, m, r, q);
}

int f3(int v, int l, int r, int ql, int qr, int q) {
    //cout << v << " " << l << " " << r << " " << ql << " " << qr << " " << q << endl;
    if (qr <= l || r <= ql) return MAX + 1;
    if (l + 1 == r) {
        if (tree[v] > q) return l;
        return MAX + 1;
    }
    int m = (l + r) / 2;
    push(v);
    if (ql <= l && r <= qr) {
        if (tree[v] <= q) return MAX + 1;
        if (tree[2 * v] > q) return f3(2 * v, l, m, ql, qr, q);
        return f3(2 * v + 1, m, r, ql, qr, q);
    }
    return min(f3(2 * v, l, m, ql, qr, q), f3(2 * v + 1, m, r, ql, qr, q));
}

int f(int v, int l, int r, int q) {
    if (l + 1 == r) {
        if (tree[v] <= q) return r;
        return l;
    }
    int m = (l + r) / 2;
    push(v);
    if (tree[2 * v] > q) return f(2 * v, l, m, q);
    return f(2 * v + 1, m, r, q);
}

int f4(int v, int l, int r, int ql, int qr, int q) {
    if (qr <= l || r <= ql) return MAX + 1;
    if (l + 1 == r) {
        if (tree2[v] <= q) return l;
        return MAX + 1;
    }
    int m = (l + r) / 2;
    push2(v);
    if (ql <= l && r <= qr) {
        if (tree2[v] > q) return MAX + 1;
        if (tree2[2 * v] <= q) return f4(2 * v, l, m, ql, qr, q);
        return f4(2 * v + 1, m, r, ql, qr, q);
    }
    return min(f4(2 * v, l, m, ql, qr, q), f4(2 * v + 1, m, r, ql, qr, q));
}

int get(int v, int l, int r, int in) {
    if (l + 1 == r) return tree[v];
    int m = (l + r) / 2;
    push(v);
    if (in < m) return get(2 * v, l, m, in);
    return get(2 * v + 1, m, r, in);
}

int get2(int v, int l, int r, int in) {
    if (l + 1 == r) return tree2[v];
    int m = (l + r) / 2;
    push2(v);
    if (in < m) return get2(2 * v, l, m, in);
    return get2(2 * v + 1, m, r, in);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        cin >> stc[i].first >> stc[i].second;
    }
    build(1, 0, m);
    build2(1, 0, m);
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int c;
            cin >> c;
            --c;
            cout << get(1, 0, m, c) << " " << get2(1, 0, m, c) << '\n';
        } else if (t == 2) {
            int l;
            cin >> l;
            int u = f2(1, 0, m, l);
            u = min(u, m);
            if (u == m) continue;
            int u2 = f3(1, 0, m, u, m, n - l);
            //cout << i << " " << u << " " << u2 << endl;
            update(1, 0, m, u, u2, n - l);
        } else {
            int l;
            cin >> l;
            int u = f(1, 0, m, l);
            u = min(u, m);
            if (u == 0) continue;
            int u2 = f4(1, 0, m, 0, u, n - l);
            //cout << i << " " << u2 << " " << u << endl;
            update2(1, 0, m, u2, u, n - l);
        }
    }
    return 0;
}
