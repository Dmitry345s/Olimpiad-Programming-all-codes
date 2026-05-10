#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5, ln = 18;
vector<vector<pair<int, int>>> g(MAX);
vector<vector<int>> up(ln, vector<int> (MAX)), up2(ln, vector<int> (MAX));
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v, int p, int c) {
    tin[v] = timer++;
    up[0][v] = p;
    up2[0][v] = c;
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
        up2[i][v] = min(up2[i - 1][v], up2[i - 1][up[i - 1][v]]);
    }
    for (auto [to, c2] : g[v]) {
        dfs(to, v, c2);
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

int get(int a, int x) {
    int ans = 1e9;
    if (a == x) {
        return ans;
    }
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(up[i][a], x)) {
            ans = min(ans, up2[i][a]);
            a = up[i][a];
        }
    }
    ans = min(up2[0][a], ans);
    return ans;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 1; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        --x;
        g[x].push_back({i, y});
    }
    dfs(0, 0, 1e9);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        int x = lca(a, b);
        cout << min(get(a, x), get(b, x)) << endl;
    }
    return 0;
}
