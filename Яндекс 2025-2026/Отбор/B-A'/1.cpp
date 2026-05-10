#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5;
vector<pair<int, int>> g[MAX];
int n;
int ans[MAX];
int used[MAX];

void dfs(int v, int p, int tp) {
    used[v] = 1;
    if (p == -1) {
        ans[v] = tp;
    } else if (ans[p] == tp) {
        ans[v] = (tp + 1) % n;
    } else {
        ans[v] = tp;
    }
    for (auto [to, tp] : g[v]) {
        if (used[to]) continue;
        dfs(to, v, tp);
    }
}

signed main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b; --c;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dfs(0, -1, 0);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << endl;
    }
    return 0;
}
