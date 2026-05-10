#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5, LN = 18;
vector<vector<int>> g(MAX);
vector<vector<int>> up(MAX, vector<int> (LN));
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v = 0, int p = 0) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
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
    if (ch(a, b)) {
        return a;
    }
    for (int i = LN - 1; i >= 0; --i) {
        if (!ch(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

signed main() {
    freopen("dynamic.in", "r", stdin);
    freopen("dynamic.out", "w", stdout);
    while (true) {
        int n;
        cin >> n;
        if (n == 0) break;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        for (int i = 0; i < n - 1; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        timer = 0;
        dfs();
        int r = 0;
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            char t;
            cin >> t;
            if (t == '!') {
                int nr;
                cin >> nr;
                --nr;
                r = nr;
            } else {
                int a, b;
                cin >> a >> b;
                --a; --b;
                cout << (lca(a, b) ^ lca(r, a) ^ lca(r, b)) + 1 << endl;
            }
        }
    }
    return 0;
}
