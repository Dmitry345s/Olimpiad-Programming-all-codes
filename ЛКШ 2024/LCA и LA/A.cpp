#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 2, LN = 18;
vector<vector<int>> g(MAX);
vector<pair<int, int>> all;
vector<int> deep(MAX), tin(MAX);

void dfs(int v = 0, int p = 0) {
    deep[v] = deep[p] + 1;
    all.push_back({deep[v], v});
    tin[v] = (int)all.size() - 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        all.push_back({deep[v], v});
    }
}

pair<int, int> sparse[2 * MAX][LN];
int max_deg[2 * MAX];

void get_sparse() {
    for (int i = 0; i < 2 * MAX; ++i) {
        for (int j = 0; j < LN; ++j) {
            sparse[i][j] = {(int)1e9, (int)1e9};
            if ((1 << j) <= i) {
                max_deg[i] = j;
            }
        }
    }
    for (int i = 0; i < (int)all.size(); ++i) {
        sparse[i][0] = all[i];
    }
    for (int i = 1; i < LN; ++i) {
        for (int j = 0; j < (int)all.size(); ++j) {
            sparse[j][i] = min(sparse[j][i - 1], sparse[min(j + (1 << (i - 1)), 2 * MAX - 1)][i - 1]);
        }
    }

}

pair<int, int> get(int l, int r) {
    int sz = r - l;
    int l2 = r - (1 << max_deg[sz]);
    return min(sparse[l][max_deg[sz]], sparse[l2][max_deg[sz]]);
}

signed main() {
    freopen("lca2.in", "r", stdin);
    freopen("lca2.out", "w", stdout);
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        int p;
        cin >> p;
        g[p].push_back(i);
        g[i].push_back(p);
    }
    dfs();
    get_sparse();
    int a1, a2;
    int x, y, z;
    cin >> a1 >> a2;
    cin >> x >> y >> z;
    int v = 0;
    long long rans = 0;
    for (int i = 0; i < m; ++i) {
        int now1 = (a1 + v) % n, now2 = a2;
        int l = tin[now1], r = tin[now2];
        pair<int, int> ans = get(min(l, r), max(l, r) + 1);
        v = ans.second;
        rans += v;
        a1 = (1ll * x * a1 + 1ll * y * a2 + z) % n;
        a2 = (1ll * x * a2 + 1ll * y * a1 + z) % n;
    }
    cout << rans << endl;
    return 0;
}
