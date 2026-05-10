#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5, INF = 1e9;
int now[MAX];
vector<int> tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {now[l]};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    for (int x : tree[2 * v]) tree[v].push_back(x);
    for (int x : tree[2 * v + 1]) tree[v].push_back(x);
    sort(tree[v].begin(), tree[v].end());
}

int get(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return r - l - (lower_bound(tree[v].begin(), tree[v].end(), x) - tree[v].begin());
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr, x) + get(2 * v + 1, m, r, ql, qr, x);
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<vector<int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        all[a[i]].push_back(i);
    }
    set<int> st;
    st.insert(INF);
    for (int i = 0; i < n; ++i) {
        all[i].push_back(INF);
        for (int j = 0; j < (int)all[i].size() - 1; ++j) {
            int u = *st.lower_bound(all[i][j]);
            if (u < all[i][j + 1]) {
                now[all[i][j]] = INF;
            } else {
                now[all[i][j]] = all[i][j + 1];
            }
            st.insert(all[i][j]);
        }
    }
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        cout << get(1, 0, n, l, r, r) << endl;
    }
    return 0;
}
