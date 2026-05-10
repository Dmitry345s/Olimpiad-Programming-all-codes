#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5, INF = 1e9, LN = 18;
vector<int> g[MAX];
int up[LN][MAX];
int tin[MAX];
int tout[MAX];
int timer = 0;

void dfs(int v, int p) {
    up[0][v] = p;
    for (int i = 1; i < LN; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    tin[v] = timer++;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer++;
}

int ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    if (ch(b, a)) return b;
    for (int i = LN - 1; i >= 0; --i) {
        if (!ch(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return up[0][a];
}

int p[MAX];
int mn[MAX];

int root(int v) {
    if (p[v] == v) return v;
    return p[v] = root(p[v]);
}

void unite(int u, int v) {
    u = root(u);
    v = root(v);
    mn[u] = min(mn[u], mn[v]);
    p[v] = u;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0, 0);
    vector<pair<int, int>> to_mns(n, {INF, INF});
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        mn[i] = i;
    }
    for (int i = n - 1; i >= 0; --i) {
        for (int to : g[i]) {
            if (to >= i) {
                int x = mn[root(to)];
                if (to_mns[i].first > x) {
                    to_mns[i].second = to_mns[i].first;
                    to_mns[i].first = x;
                } else if (to_mns[i].second > x) {
                    to_mns[i].second = x;
                }
            }
        }
        for (int to : g[i]) {
            if (to >= i) {
                unite(to, i);
            }
        }
    }
    vector<int> ans(n);
    vector<int> ch(n);
    for (int i = 0; i < n; ++i) {
        ch[i] = min((int)g[i].size(), 2);
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (ans[i] == 0) {
            cnt++;
            ans[i] = cnt;
        }
        if (ch[i] == 0) continue;
        auto [u, v] = to_mns[i];
        if (u < INF && ans[u] == 0) {
            int wsi = ch[i];
            int wsu = ch[u];
            int tt = lca(i, u);
            int y = i;
            int fl = (ans[tt] == 0 || tt == i);
            while (y != tt) {
                if (ans[y] != 0 && y != i) {
                    fl = 0;
                }
                y = up[0][y];
            }
            y = u;
            while (y != tt) {
                if (ans[y] != 0 && y != i) {
                    fl = 0;
                }
                y = up[0][y];
            }
            if (!fl) continue;
            ans[tt] = ans[i];
            ch[tt] = 0;
            y = i;
            while (y != tt) {
                ans[y] = ans[i];
                ch[y] = 0;
                y = up[0][y];
            }
            y = u;
            while (y != tt) {
                ans[y] = ans[i];
                ch[y] = 0;
                y = up[0][y];
            }
            ch[i] = wsi - 1;
            ch[u] = wsu - 1;
        }
        if (ch[i] == 0) continue;
        if (v < INF && ans[v] == 0) {
            int wsi = ch[i];
            int wsv = ch[v];
            int tt = lca(i, v);
            int y = i;
            int fl = (ans[tt] == 0 || tt == i);
            while (y != tt) {
                if (ans[y] != 0 && y != i) {
                    fl = 0;
                }
                y = up[0][y];
            }
            y = v;
            while (y != tt) {
                if (ans[y] != 0 && y != i) {
                    fl = 0;
                }
                y = up[0][y];
            }
            if (!fl) continue;
            ans[tt] = ans[i];
            ch[tt] = 0;
            y = i;
            while (y != tt) {
                ans[y] = ans[i];
                ch[y] = 0;
                y = up[0][y];
            }
            y = v;
            while (y != tt) {
                ans[y] = ans[i];
                ch[y] = 0;
                y = up[0][y];
            }
            ch[i] = wsi - 1;
            ch[v] = wsv - 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
