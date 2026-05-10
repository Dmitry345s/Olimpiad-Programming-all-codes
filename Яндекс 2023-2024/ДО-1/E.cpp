#include<bits/stdc++.h>

using namespace std;

struct node {
    int mx, sm;
    node() {
        mx = 0;
        sm = 1;
    }
    node(int mx1, int sm1) {
        mx = mx1;
        sm = sm1;
    }
};

int mod = 1e9 + 7;

node operator + (node a, node b) {
    if (a.mx > b.mx) {
        return a;
    }
    if (b.mx > a.mx) {
        return b;
    }
    if (a.mx == 0) {
        return node();
    }
    return node(a.mx, (a.sm + b.sm) % mod);
}

int MAX = 1e5;
vector<node> tree(4 * MAX);

void update(int v, int l, int r, int id, node x) {
    if (l + 1 == r) {
        tree[v] = tree[v] + x;
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

node get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return node();
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
    vector<int> a(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back(a[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i) {
        int j = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
        node ans = get(1, 0, n, 0, j);
        ans.mx += 1;
        update(1, 0, n, j, ans);
    }
    cout << get(1, 0, n, 0, n).sm << endl;
    return 0;
}
