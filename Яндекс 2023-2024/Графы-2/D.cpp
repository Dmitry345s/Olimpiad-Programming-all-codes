#include<bits/stdc++.h>

using namespace std;

int x, MAX = 1e5 + 5;
vector<int> p(MAX);

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

struct edge {
    int to, w;
};

vector<vector<edge>> g(MAX);
vector<long long> dp(MAX), sz(MAX), dp2(MAX);
long long ans = 0;

void dfs(int v, int p = -1) {
    sz[v] = 1;
    dp2[v] = 1;
    for (auto [to, w] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        if (w == x) {
            dp2[v] += dp2[to];
            dp[v] += dp2[to];
        } else if (w < x) {
            dp2[v] += dp2[to];
            dp[v] += dp[to];
        }
        sz[v] += sz[to];
    }
}

void dfs2(int v, int p = -1) {
    long long y = dp2[v], y2 = dp[v];
    for (auto [to, w] : g[v]) {
        if (to == p) continue;
        dfs2(to, v);
        if (w == x) {
            y -= dp2[to];
            ans += dp2[to] * (y);
        } else if (w < x) {
            y -= dp2[to];
            y2 -= dp[to];
            ans += dp[to] * (y);
            ans += (dp2[to] - dp[to]) * (y2);
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m >> x;
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    vector<array<int, 3>> ftr(m);
    for (int i = 0; i < m; ++i) {
        cin >> ftr[i][1] >> ftr[i][2] >> ftr[i][0];
        --ftr[i][1]; --ftr[i][2];
    }
    sort(ftr.begin(), ftr.end());
    for (auto [w, v, to] : ftr) {
        if (root(v) != root(to)) {
            g[v].push_back({to, w});
            g[to].push_back({v, w});
            p[root(v)] = root(to);
        }
    }
    dfs(0);
    dfs2(0);
    cout << ans << endl;
    return 0;
}
