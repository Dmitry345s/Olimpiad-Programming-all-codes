#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
string s;
vector<array<int, 26>> tree(4 * MAX);
vector<int> update_tree(4 * MAX);

array<int, 26> mmerge(array<int, 26> a, array<int, 26> b) {
    for (int i = 0; i < 26; ++i) {
        a[i] += b[i];
    }
    return a;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v][(int)s[l] - 97] = 1;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = mmerge(tree[2 * v], tree[2 * v + 1]);
}

array<int, 26> ch;

void push(int v, int l, int r) {
    if (update_tree[v] == 0) return;
    array<int, 26> tol = ch, tor = ch;
    int m = (l + r) / 2;
    if (update_tree[v] == 1) {
        int sz = m - l;
        tor = tree[v];
        for (int i = 0; i < 26; ++i) {
            if (sz == 0) break;
            int del = min(sz, tree[v][i]);
            tol[i] = del;
            tor[i] -= del;
            sz -= del;
        }
    } else {
        int sz = r - m;
        tol = tree[v];
        for (int i = 0; i < 26; ++i) {
            if (sz == 0) break;
            int del = min(sz, tree[v][i]);
            tor[i] = del;
            tol[i] -= del;
            sz -= del;
        }
    }
    tree[2 * v] = tol;
    tree[2 * v + 1] = tor;
    update_tree[2 * v] = update_tree[v];
    update_tree[2 * v + 1] = update_tree[v];
    update_tree[v] = 0;
}

array<int, 26> d;

void get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        d = mmerge(d, tree[v]);
        return;
    }
    push(v, l, r);
    int m = (l + r) / 2;
    get(2 * v, l, m, ql, qr);
    get(2 * v + 1, m, r, ql, qr);
}

void update(int v, int l, int r, int ql, int qr, int t) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] = ch;
        int sz = r - l;
        for (int i = 0; i < 26; ++i) {
            if (sz == 0) break;
            int del = min(d[i], sz);
            tree[v][i] = del;
            d[i] -= del;
            sz -= del;
        }
        update_tree[v] = t;
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r);
    if (t == 1) {
        update(2 * v, l, m, ql, qr, t);
        update(2 * v + 1, m, r, ql, qr, t);
    } else {
        update(2 * v + 1, m, r, ql, qr, t);
        update(2 * v, l, m, ql, qr, t);
    }
    tree[v] = mmerge(tree[2 * v], tree[2 * v + 1]);
}

string ans;

void lg(int v, int l, int r) {
    if (l + 1 == r) {
        for (int i = 0; i < 26; ++i) {
            if (tree[v][i]) {
                ans.push_back((char)(i + 97));
                break;
            }
        }
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r);
    lg(2 * v, l, m);
    lg(2 * v + 1, m, r);
}

signed main() {
    for (int i = 0; i < 26; ++i) {
        ch[i] = 0;
    }
    int n, q;
    cin >> n >> q;
    cin >> s;
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        int l, r, k;
        cin >> l >> r >> k;
        --l;
        if (!k) --k;
        d = ch;
        get(1, 0, n, l, r);
        update(1, 0, n, l, r, k);
    }
    lg(1, 0, n);
    cout << ans << endl;
    return 0;
}
