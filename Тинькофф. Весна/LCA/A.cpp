#include<iostream>
#include<vector>

using namespace std;

int MAX = 1e5, l = 17, timer = 0;
vector<int> tin(MAX), tout(MAX), used(MAX), cost(MAX);
vector<vector<int>> up(l, vector<int> (MAX));
vector<vector<int>> g(MAX);
vector<long long> d(MAX);

void dfs(int v, int p = 0) {
    used[v] = 1;
    tin[v] = ++timer;
    up[0][v] = p;
    d[v] = d[p] + cost[v];
    for (int i = 1; i < l; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to, v);
        }
    }
    tout[v] = ++timer;
}

bool upper(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (upper(a, b)) return a;
    if (upper(b, a)) return b;
    for (int i = l - 1; i >= 0; --i) {
        if (!upper(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> cost[i];
    }
    for (int l = 0; l < n - 1; ++l) {
        int i, j;
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }
    dfs(0);
    int m;
    cin >> m;
    for (int _ = 0; _ < m; ++_) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int x = lca(a, b);
        cout << d[a] + d[b] - 2 * d[x] + cost[x] << endl;
    }
    return 0;
}
