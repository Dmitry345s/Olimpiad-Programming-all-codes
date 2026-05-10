#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<int> col(MAX);
vector<int> ans(MAX);
vector<vector<int>> g(MAX);

void dfs(int v, int p, vector<int> & dp, int now_ans) {
    int j = upper_bound(dp.begin(), dp.end(), col[v]) - dp.begin();
    int prev = dp[j], del = 0;
    if (dp[j - 1] < col[v]) {
        if (dp[j] == 2e9) {
            del = -1;
            now_ans += 1;
        }
        dp[j] = col[v];
    }
    ans[v] = now_ans;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v, dp, now_ans);
    }
    dp[j] = prev;
    now_ans += del;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> col[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    vector<int> dp(n + 1, 2e9);
    dp[0] = -1e9;
    dfs(0, 0, dp, 0);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
