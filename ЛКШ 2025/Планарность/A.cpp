#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5;

vector<int> g[MAX];
int used[MAX];

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to]) continue;
        dfs(to);
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    int c = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            c++;
            dfs(i);
        }
    }
    cout << m + 1 + c - n << endl;
    return 0;
}
