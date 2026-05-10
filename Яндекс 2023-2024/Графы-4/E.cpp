#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5, ln = 18;
vector<vector<pair<int, int>>> g(MAX);
vector<vector<int>> up(ln, vector<int> (MAX)), up2(ln, vector<int> (MAX, -3));
vector<int> tin(MAX), tout(MAX), used(MAX);
int timer = 0;

void dfs(int v, int p, int c, int num) {
    used[v] = num;
    tin[v] = timer++;
    up[0][v] = p;
    up2[0][v] = c;
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
        up2[i][v] = max(up2[i - 1][v], up2[i - 1][up[i - 1][v]]);
    }
    for (auto [to, c2] : g[v]) {
        if (to == p) continue;
        dfs(to, v, c2, num + c2);
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

pair<int, int> lca(int a, int b) {
    if (ch(a, b)) return {a, -1};
    int ans = -3;
    for (int i = ln - 1; i >= 0; --i) {
        if (!ch(up[i][a], b)) {
            ans = max(ans, up2[i][a]);
            a = up[i][a];
        }
    }
    return {up[0][a], max(ans, up2[0][a])};
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back({b, 0});
        g[b].push_back({a, -1});
    }
    dfs(0, 0, -4, -1);
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        pair<int, int> g = lca(a, b);
        if (g.second == -1 && used[g.first] == used[b]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
