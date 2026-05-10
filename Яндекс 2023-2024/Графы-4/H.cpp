#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math")

using namespace std;

const int MAX = 1e6, ln = 20;
vector<int> g[MAX];
int up[ln][MAX];
int tin[MAX], tout[MAX];
int timer = 0;

void dfs(int & v, int & p) {
    tin[v] = ++timer;
    up[0][v] = p;
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int i = 0; i < (int)g[v].size(); ++i) {
        dfs(g[v][i], v);
    }
    tout[v] = ++timer;
}

int ch(int & a, int & b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int & b) {
    if (ch(a, b)) return a;
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    int p;
    for (int i = 1; i < n; ++i) {
        cin >> p;
        g[p].push_back(i);
    }
    int cts = 0;
    dfs(cts, cts);
    int a[2];
    cin >> a[0] >> a[1];
    int x, y, z;
    cin >> x >> y >> z;
    long long ans = 0;
    for (int i = 0; i < m; ++i) {
        ans += lca(a[0], a[1]);
        a[0] = (1ll * x * a[0] + 1ll * y * a[1] + z) % n;
        a[1] = (1ll * x * a[1] + 1ll * y * a[0] + z) % n;
    }
    cout << ans << '\n';
}
