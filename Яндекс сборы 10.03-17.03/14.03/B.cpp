#include<bits/stdc++.h>

using namespace std;

const int MAX = 2001;
int tree[4 * MAX];

int mrg(int a, int b) {
    if (a == -1) return b;
    if (b == -1) return a;
    cout << "? " << a + 1 << " " << b + 1 << endl;
    int ans;
    cin >> ans;
    if (ans) {
        return b;
    }
    return a;
}

void upd(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return;
    if (l + 1 == r) {
        tree[v] = l;
        return;
    }
    int m = (l + r) / 2;
    upd(2 * v, l, m, ql, qr);
    upd(2 * v + 1, m, r, ql, qr);
    tree[v] = mrg(tree[2 * v], tree[2 * v + 1]);
}

void dupd(int v, int l, int r, int in) {
    if (l + 1 == r) {
        tree[v] = -1;
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        dupd(2 * v, l, m, in);
    } else {
        dupd(2 * v + 1, m, r, in);
    }
    tree[v] = mrg(tree[2 * v], tree[2 * v + 1]);
}

signed main() {
    int n;
    cin >> n;
    int nl = 0;
    fill(tree, tree + 4 * MAX, -1);
    while (n--) {
        int x;
        cin >> x;
        upd(1, 0, MAX, nl, nl + x);
        nl += x;
        int u = tree[1];
        dupd(1, 0, MAX, u);
        cout << "! " << u + 1 << endl;
    }
    return 0;
}
