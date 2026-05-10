#include<bits/stdc++.h>

using namespace std;

int MAX = 3e5;
vector<int> b(MAX);
vector<vector<int>> tree(4 * MAX);

vector<int> mmerge(vector<int> a, vector<int> b) {
    vector<int> c;
    for (int i = 0; i < (int)a.size(); ++i) {
        c.push_back(a[i]);
    }
    for (int i = 0; i < (int)b.size(); ++i) {
        c.push_back(b[i]);
    }
    sort(c.begin(), c.end());
    return c;
}

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {b[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = mmerge(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return (r - l) - (upper_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin());
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr, x) + get(2 * v + 1, m, r, ql, qr, x);
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<int, int> mp;
    for (int i = n - 1; i >= 0; --i) {
        if (mp.find(a[i]) == mp.end()) {
            b[i] = 1e9;
        } else {
            b[i] = mp[a[i]];
        }
        mp[a[i]] = i;
    }
    build(1, 0, n);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << get(1, 0, n, l, r, r - 1) << endl;
    }
    return 0;
}
