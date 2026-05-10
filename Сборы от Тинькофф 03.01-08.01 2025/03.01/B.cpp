#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 3e5 + 5, INF = 1e18;
int tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = INF;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

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

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return INF;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return min(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> all(m + 1);
    vector<vector<pair<int, int>>> all2(m + 2);
    for (int i = 0; i < n; ++i) {
        int l, r, c;
        cin >> l >> r >> c;
        all[r].push_back({l, c});
        all2[l].push_back({r, c});
    }
    vector<int> dp(m + 1, INF);
    build(1, 0, m + 2);
    dp[0] = 0;
    update(1, 0, m + 2, 0, 0);
    for (int r = 1; r <= m; ++r) {
        for (auto [l, c] : all[r]) {
            dp[r] = min(dp[r], get(1, 0, m + 2, l - 1, r) + c);
            update(1, 0, m + 2, r, dp[r]);
        }
    }
    vector<int> dp2(m + 2, INF);
    build(1, 0, m + 2);
    dp2[m + 1] = 0;
    update(1, 0, m + 2, m + 1, 0);
    for (int l = m; l >= 1; --l) {
        for (auto [r, c] : all2[l]) {
            dp2[l] = min(dp2[l], get(1, 0, m + 2, l + 1, r + 2) + c);
            update(1, 0, m + 2, l, dp2[l]);
        }
    }
    int ans = INF;
    for (int i = 1; i <= m; ++i) {
        ans = min(ans, dp[i - 1] + dp2[i + 1]);
        //cout << ans << " " << dp[i - 1] << " " << dp2[i + 1] << endl;
    }
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
