#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 2e5 + 3;
vector<long long> a(MAX), p(MAX), tree(4 * MAX);

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
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

long long my_get(int l, int r, int n) {
    if (l + 1 >= r) {
        return 0;
    }
    int x = get(1, 0, n, l, r);
    int j = p[x];
    long long ans1 = my_get(l, j, n), ans2 = my_get(j + 1, r, n);
    long long del1 = j - p[get(1, 0, n, l, j)], del2 = p[get(1, 0, n, j + 1, r)] - j;
    if (j + 1 == r) {
        del2 = 0;
    }
    if (l == j) {
        del1 = 0;
    }
    return max(ans1 + del1, ans2 + del2);
}


vector<vector<int>> g(MAX);
vector<int> dp(MAX), dep(MAX);
int cnt = 0;

void dfs(int v, int x, int p = -1) {
    dp[v] = a[v];
    for (int to : g[v]) {
        if (to == p) continue;
        if (a[to] > x) continue;
        dep[to] = dep[v] + 1;
        dfs(to, x, v);
        dp[v] = max(dp[v], dp[to]);
    }
}

vector<vector<pair<int, int>>> g2(MAX);

void dfs2(int v, int ps = -1) {
    for (int to : g[v]) {
        if (to == ps) continue;
        g2[v].push_back({p[dp[to]], dep[v] - dep[p[dp[to]]]});
        g2[p[dp[to]]].push_back({v, dep[v] - dep[p[dp[to]]]});
        dfs2(to, v);
    }
}

vector<int> dp2(MAX);

void dfs3(int v, int p = -1) {
    for (auto [to, w] : g2[v]) {
        if (to == p) continue;
        dp2[to] = dp[v] + w;
        dfs3(to, v);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        p[a[i]] = i;
    }
    int flag = 1;
    for (int i = 0; i < n - 1; ++i) {
        int v, to;
        cin >> v >> to;
        --v; --to;
        g[v].push_back(to);
        g[to].push_back(v);
        if (v + 1 != to) {
            flag = 0;
        }
    }
    int j = p[n];
    dep[j] = 0;
    dfs(j, n);
    dfs2(j);
    dp2[j] = 0;
    dfs3(j);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans = max(ans, dp2[i]);
    }
    cout << ans << endl;
    return 0;
}
