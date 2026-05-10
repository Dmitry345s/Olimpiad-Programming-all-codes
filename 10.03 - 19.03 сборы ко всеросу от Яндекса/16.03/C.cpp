#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 1;
int a[MAX];
pair<int, int> tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = {a[l], l};
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

const int INF = 1e9;

void update(int v, int l, int r, int x, int in) {
    if (l + 1 == r) {
        tree[v] = {x, l};
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, x, in);
    } else {
        update(2 * v + 1, m, r, x, in);
    }
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

pair<int, int> get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return {INF, INF};
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return min(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

int solve(int l, int r, int n, int u) {
    if (l == r) return 0;
    int mx = get(1, 0, n, l, r).first;
    vector<int> all;
    all.push_back(l - 1);
    while (true) {
        auto [nm, in] = get(1, 0, n, l, r);
        if (nm != mx) break;
        all.push_back(in);
        update(1, 0, n, INF, in);
    }
    all.push_back(r);
    int ans = 0;
    for (int i = 0; i < (int)all.size() - 1; ++i) {
        int y = solve(all[i] + 1, all[i + 1], n, mx);
        ans = max(ans, min(y + mx - u, r - l));
    }
    //cout << l << " " << r << " " << ans << endl;
    return ans;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }
    build(1, 0, m);
    cout << solve(0, m, m, 0) << endl;
    return 0;
}
