#include<bits/stdc++.h>

using namespace std;

struct edge {
    int to, c;
};

int MAX = 1e5;
vector<vector<edge>> g(MAX);
vector<int> used(MAX), dp(MAX, 2e9);
int k;

void dfs(int v) {
    used[v] = 1;
    if (v == k) {
        dp[v] = 0;
    }
    for (auto [to, c] : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
        dp[v] = min(dp[to] + c, dp[v]);
    }
}

signed main() {
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    --s; --t;
    k = s;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[b].push_back({a, c});
    }
    dfs(t);
    if (dp[t] >= 1e9) {
        cout << "Unreachable" << endl;
    } else {
        cout << dp[t];
    }
    return 0;
}
