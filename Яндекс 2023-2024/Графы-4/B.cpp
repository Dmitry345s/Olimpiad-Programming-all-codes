#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5, ln = 18;
vector<int> c(MAX);
vector<vector<int>> g(MAX), up(ln, vector<int> (MAX));
vector<int> tin(MAX), tout(MAX);
vector<long long> cnt(MAX);
int timer = 0;

void dfs(int v, int p) {
    tin[v] = timer++;
    up[0][v] = p;
    cnt[v] = cnt[p] + c[v];
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0, 0);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int x = lca(a, b);
        cout << cnt[a] + cnt[b] - 2 * cnt[x] + c[x] << endl;
    }
    return 0;
}
