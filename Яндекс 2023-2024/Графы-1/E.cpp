#include<bits/stdc++.h>

using namespace std;

struct edge {
    int to, c;
};

int MAX = 1e5;
vector<vector<edge>> g(MAX);
vector<int> sz(MAX, 1);
int n;
long long ans = 0;

void dfs(int v, int p) {
    for (auto [to, c] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
        ans += sz[to] * (long long)(n - sz[to]) * (long long)c;
    }
}

signed main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dfs(0, 0);
    cout << ans * 2 << endl;
    return 0;
}
