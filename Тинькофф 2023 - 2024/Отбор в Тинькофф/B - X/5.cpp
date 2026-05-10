#include<bits/stdc++.h>
#define int long long

using namespace std;

int MAX = 2e5, ln = 19;
vector<vector<int>> g(MAX), up(ln, vector<int> (MAX));
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v, int p = 0) {
    up[0][v] = p;
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    tin[v] = timer++;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer++;
}

bool check(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    for (int i = ln - 1; i >= 0; --i) {
        if (!check(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return a;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(0);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int s, t;
        cin >> s >> t;
        --s; --t;
        if (check(s, t)) {
            cout << lca(t, s) + 1 << endl;
        } else {
            cout << up[0][s] + 1 << endl;
        }
    }
    return 0;
}
