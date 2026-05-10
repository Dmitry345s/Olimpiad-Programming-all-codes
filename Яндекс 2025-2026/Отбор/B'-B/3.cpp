#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5, MANS = 1e6;

vector<int> g[MAX];
int used[MAX];
int ans = 0;

void dfs(int v) {
    ans++;
    if (ans >= MANS) return;
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
        if (ans >= MANS) return;
    }
    used[v] = 0;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    cout << ans << endl;
    return 0;
}
