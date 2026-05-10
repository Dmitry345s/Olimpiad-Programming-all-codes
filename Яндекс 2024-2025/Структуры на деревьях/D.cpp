#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1, LN = 18;
vector<int> g[MAX];
int up[MAX][LN];
int timer = 0;
int tin[MAX], tout[MAX];

void dfs(int v, int p = 0) {
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    tin[v] = timer++;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    if (ch(b, a)) return b;
    for (int i = LN - 1; i >= 0; --i) {
        if (!ch(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

signed main() {
    int n;
    while (cin >> n) {
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
        dfs(0);
        int r = 0;
        int m;
        cin >> m;
        for (int i = 0; i < m; ++i) {
            char t;
            cin >> t;
            if (t == '!') {
                cin >> r;
                r--;
            } else {
                int a, b;
                cin >> a >> b;
                --a; --b;
                //cout << lca(a, b) << endl;
                cout << (lca(a, b) ^ lca(a, r) ^ lca(b, r)) + 1 << '\n';
            }
        }
    }
    return 0;
}
