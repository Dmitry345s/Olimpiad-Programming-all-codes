#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1, SZ = 35;
array<int, SZ> tree[4 * MAX];
int a[MAX];

array<int, SZ> mmerge(array<int, SZ> a, array<int, SZ> b) {
    vector<int> all;
    for (int i = 0; i < SZ; ++i) {
        all.push_back(a[i]);
        all.push_back(b[i]);
    }
    sort(all.rbegin(), all.rend());
    for (int i = 0; i < SZ; ++i) {
        a[i] = all[i];
    }
    return a;
}

void build (int v, int l, int r) {
    if (l + 1 == r) {
        tree[v][0] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = mmerge(tree[2 * v], tree[2 * v + 1]);
}

array<int, SZ> ch;

array<int, SZ> get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) return ch;
    if (ql <= l && r <= qr) return tree[v];
    int m = (l + r) / 2;
    return mmerge(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    build(1, 0, n);
    for (int i = 0; i < SZ; ++i) {
        ch[i] = 0;
    }
    cout.precision(10);
    cout << fixed;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        array<int, SZ> ta = get(1, 0, n, l, r);
        long double ans = 0;
        for (int j = 0; j < SZ; ++j) {
            if (j != SZ - 1 && ta[j + 1] != 0) {
                ans += (long double)ta[j] / (1ll << (j + 1));
            } else {
                ans += (long double)ta[j] / (1ll << j);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
