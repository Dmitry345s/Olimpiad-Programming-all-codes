#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<vector<pair<int, int>>> g(MAX);
vector<int> used(MAX);

void dfs(int v) {
    used[v] = 1;
    for (auto [t, to] : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

vector<int> ans, ans2;
vector<int> used2(MAX);

void dfs2(int v) {
    used[v] = 1;
    int i = 0;
    set<int> st;
    while(i < (int)g[v].size() && g[v][i].first == -1) {
        if (!used[g[v][i].second]) {
            st.insert(g[v][i].second);
            dfs2(g[v][i].second);
        }
        ++i;
    }
    int j = i - 1;
    while (j >= 0) {
        if (st.find(g[v][j].second) != st.end()) {
            ans2.push_back(g[v][j].second);
        }
        --j;
    }
    int last = i;
    ans.push_back(v);
    set<int> st2;
    while(i < (int)g[v].size() && g[v][i].first == 1) {
        if (!used[g[v][i].second]) {
            st2.insert(g[v][i].second);
            dfs2(g[v][i].second);
        }
        ++i;
    }
    j = last;
    while (j < (int)g[v].size()) {
        if (st2.find(g[v][j].second) != st2.end()) {
            ans2.push_back(g[v][j].second);
        }
        ++j;
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({1, b});
        g[b].push_back({-1, a});
    }
    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
    }
    dfs(1);
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            cout << 0 << endl;
            return 0;
        }
    }
    used.assign(MAX, 0);
    dfs2(1);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n - 1; ++i) {
        cout << ans2[i] << " ";
    }
    return 0;
}
