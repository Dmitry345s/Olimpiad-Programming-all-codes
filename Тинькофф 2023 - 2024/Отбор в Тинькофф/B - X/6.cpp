#include<bits/stdc++.h>
#define int long long

using namespace std;

struct node {
    int ans, ansl, ansr, ansrl;
};

node operator + (node a, node b) {
    node ret = {0, 0, 0, 0};
    ret.ans = max(a.ansr + b.ans, a.ans + b.ansl);
    ret.ansl = max(a.ansl + b.ansl, a.ansrl + b.ans);
    ret.ansr = max(a.ansr + b.ansr, a.ans + b.ansrl);
    ret.ansrl = max(a.ansl + b.ansrl, a.ansrl + b.ansr);
    return ret;
}

int MAX = 3e5;
vector<node> tree(4 * MAX);
vector<int> a(MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {a[l], 0, 0, -a[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] = {x, 0, 0, -x};
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v + 1, l, m, id, x);
    } else {
        update(2 * v + 2, m, r, id, x);
    }
    tree[v] = tree[2 * v + 1] + tree[2 * v + 2];
}

signed main() {
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(0, 0, n);
    cout << tree[0].ans << endl;
    for (int i = 0; i < q; ++i) {
        int ql, qr;
        cin >> ql >> qr;
        --ql; --qr;
        swap(a[ql], a[qr]);
        update(0, 0, n, ql, a[ql]);
        update(0, 0, n, qr, a[qr]);
        cout << tree[0].ans << endl;
    }
    return 0;
}
