#include<bits/stdc++.h>

using namespace std;

int MAX = 3e5;
vector<vector<int>> g(MAX);
vector<int> dp(MAX), used(MAX);
set<int> st;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
    }
    for (int to : g[v]) {
        st.erase(dp[to]);
    }
    dp[v] = *st.begin();
    for (int to : g[v]) {
        st.insert(dp[to]);
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
    }
    for (int i = 0; i <= n; ++i) {
        st.insert(i);
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << dp[i] << endl;
    }
    return 0;
}
