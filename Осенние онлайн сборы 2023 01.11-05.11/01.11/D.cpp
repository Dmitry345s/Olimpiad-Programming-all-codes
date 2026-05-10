#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 2e6;
vector<int> p(MAX), c(MAX), dp(MAX), w(MAX);
vector<vector<pair<int, int>>> g2(MAX);
vector<int> ans, ans2;

int root(int v) {
    if (v == p[v]) {
        return v;
    }
    return p[v] = root(p[v]);
}

void dfs(int v, int ps = 0) {
    for (auto [to, j] : g2[v]) {
        if (to == ps) continue;
        dfs(to, v);
    }
    dp[v] = c[v];
    for (auto [to, j] : g2[v]) {
        if (to == ps) continue;
        if (dp[to] + dp[v] >= w[j]) {
            cout << j + 1 << endl;
            dp[v] += dp[to] - w[j];
        } else {
            ans2.push_back(j);
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, gr;
    cin >> n >> m >> gr;
    int sum2 = 0;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
        sum2 += c[i];
        p[i] = i;
    }
    vector<pair<int, int>> ed(m);
    vector<pair<int, int>> g;
    for (int i = 0; i < m; ++i) {
        cin >> ed[i].first >> ed[i].second;
        --ed[i].first; --ed[i].second;
        cin >> w[i];
        g.push_back({w[i], i});
    }
    sort(g.begin(), g.end());
    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        int j = g[i].second;
        int v = ed[j].first, to = ed[j].second;
        if (root(to) == root(v)) {
            continue;
        }
        g2[v].push_back({to, j});
        g2[to].push_back({v, j});
        sum += w[j];
        p[root(to)] = root(v);
        cnt++;
    }
    if (sum > sum2 || cnt != n - 1) {
        cout << -1 << endl;
        return 0;
    }
    cout << n - 1 << endl;
    dfs(0);
    reverse(ans2.begin(), ans2.end());
    for (int i = 0; i < (int)ans2.size(); ++i) {
        cout << ans2[i] + 1 << endl;
    }
    return 0;
}
