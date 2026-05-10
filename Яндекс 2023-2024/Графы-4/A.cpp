#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5, ln = 18;
vector<vector<int>> g(MAX), up(ln, vector<int> (MAX));
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v, int p) {
    tin[v] = timer++;
    up[0][v] = p;
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int to : g[v]) {
        dfs(to, v);
    }
    tout[v] = timer++;
}

bool check(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (check(a, b)) return a;
    for (int i = ln - 1; i >= 0; --i) {
        if (!check(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    dfs(0, 0);
    vector<int> a(2 * m);
    cin >> a[0] >> a[1];
    int x, y, z;
    cin >> x >> y >> z;
    for (int i = 2; i < 2 * m; ++i) {
        a[i] = (1ll * x * a[i - 2] + 1ll * y * a[i - 1] + z) % n;
    }
    long long ans = 0;
    int last = 0;
    for (int i = 0; i < m; ++i) {
        int x = lca((a[2 * i] + last) % n, a[2 * i + 1]);
        //cout << x << endl;
        ans += x;
        last = x;
    }
    cout << ans << endl;
    return 0;
}
