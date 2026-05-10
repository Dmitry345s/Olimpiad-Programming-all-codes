#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5;
vector<int> sz(MAX);

bool cmp(int a, int b) {
    if (sz[a] == sz[b]) {
        return a < b;
    }
    return sz[a] < sz[b];
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> to_go(n);
    for (int i = 0; i < n; ++i) {
        sz[i] = (int)g[i].size();
        to_go[i] = i;
    }
    sort(to_go.begin(), to_go.end());
    vector<vector<int>> g_new(n);
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (sz[to] > sz[i] || (sz[to] == sz[i] && to > i)) {
                g_new[i].push_back(to);
            }
        }
    }
    vector<int> used(n);
    int ans = 0;
    for (int v : to_go) {
        for (int to : g_new[v]) {
            used[to] = 1;
        }
        for (int to : g_new[v]) {
            for (int to2 : g_new[to]) {
                if (used[to2]) {
                    ans++;
                }
            }
        }
        for (int to : g_new[v]) {
            used[to] = 0;
        }
    }
    cout << ans << endl;
    return 0;
}
