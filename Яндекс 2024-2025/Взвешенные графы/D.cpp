#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1, LN = 18, INF = 2e9;
int p[MAX];

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

void unite(int v, int u) { p[root(v)] = root(u); }

vector<pair<int, int>> g[MAX];
int up[MAX][LN][2];
int timer = 0;
int h[MAX];

void dfs(int v, int ps = 1, int last = INF) {
    up[v][0][0] = ps;
    up[v][0][1] = last;
    for (int i = 1; i < LN; ++i) {
        up[v][i][0] = up[up[v][i - 1][0]][i - 1][0];
        up[v][i][1] = min(up[v][i - 1][1], up[up[v][i - 1][0]][i - 1][1]);
    }
    h[v] = h[ps] + 1;
    for (auto [to, c] : g[v]) {
        if (to == ps) continue;
        dfs(to, v, c);
    }
}

int lca(int a, int b) {
    if (h[a] < h[b]) {
        swap(a, b);
    }
    int x = h[a] - h[b];
    int ans = INF;
    for (int i = LN - 1; i >= 0; --i) {
        if ((x >> i) & 1) {
            ans = min(up[a][i][1], ans);
            a = up[a][i][0];
        }
    }
    for (int i = LN - 1; i >= 0; --i) {
        if (up[a][i][0] != up[b][i][0]) {
            ans = min(ans, min(up[a][i][1], up[b][i][1]));
            a = up[a][i][0];
            b = up[b][i][0];
        }
    }
    if (a != b) {
        ans = min(ans, min(up[a][0][1], up[b][0][1]));
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i) p[i] = i;
    for (int i = m; i >= 1; --i) {
        for (int j = 2 * i; j <= n; j += i) {
            if (root(i) == root(j)) continue;
            g[j].push_back({i, i});
            g[i].push_back({j, i});
            //cout << i << " " << j << endl;
            unite(i, j);
            //cout << (root(20) == root(9)) << endl;
        }
    }
    dfs(1);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        cout << m + 1 - lca(a, b) << endl;
    }
    return 0;
}
