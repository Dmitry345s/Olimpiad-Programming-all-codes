#include<bits/stdc++.h>

using namespace std;

const int MAX = 151, INF = 1e9;
vector<vector<int>> dp(MAX, vector<int> (MAX));
vector<vector<int>> g(MAX);

void dfs(int v, int p) {
    dp[v][1] = (int)g[v].size() - 1;
    if (p == -1) {
        dp[v][1]++;
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        dp[to][0] = 1;
        for (int i = MAX - 1; i >= 0; --i) {
            for (int cnt = 0; cnt < MAX; ++cnt) {
                if (cnt > i) break;
                dp[v][i] = min(dp[v][i], dp[v][i - cnt] + dp[to][cnt] - 1);
            }
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int ans = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            dp[j].assign(MAX, INF);
        }
        dfs(i, -1);
        ans = min(ans, dp[i][m]);
    }
    cout << ans << endl;
    return 0;
}
