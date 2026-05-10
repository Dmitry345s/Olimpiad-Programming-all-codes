#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")

using namespace std;

int MAX = 1e4;
vector<vector<int>> g(MAX), cmp(MAX);
vector<int> a(MAX), used(MAX), b(MAX);

void dfs(int v, int num) {
    used[v] = 1;
    cmp[num].push_back(a[v]);
    b[v] = num;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to, num);
        }
    }
}

vector<int> tree(4 * MAX + 4);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x);
    } else {
        update(2 * v + 1, m, r, id, x);
    }
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr) {
    if (r <= ql || qr <= l) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr), get(2 * v + 1, m, r, ql, qr));
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        int v, to;
        cin >> v >> to;
        --v; --to;
        g[v].push_back(to);
        g[to].push_back(v);
    }
    int num = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i, num);
            sort(cmp[num].rbegin(), cmp[num].rend());
            num++;
        }
    }
    vector<int> dp(n + 1, 2e9);
    dp[0] = -1;
    for (int i = 0; i < n; ++i) {
        int now = n;
        for (int j = 0; j < (int)cmp[b[i]].size(); ++j) {
            while (dp[now] >= cmp[b[i]][j]) {
                --now;
            }
            dp[now + 1] = cmp[b[i]][j];
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (dp[i] != 2e9) {
            ans = i;
        }
    }
    cout << ans << endl;
    return 0;
}
