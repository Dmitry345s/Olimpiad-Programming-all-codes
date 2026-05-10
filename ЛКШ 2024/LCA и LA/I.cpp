#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e6 + 1, MAXM = 1e7 + 1;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
vector<int> p(MAX);
vector<vector<int>> ch(MAX);

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return p[v] = root(p[v]);
}

void unite(int v, int u) {
    p[u] = v;
}

long long ans = 0;

void dfs(int v = 0, int p = 0) {
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        unite(v, to);
    }
    //cout << v << endl;
    for (auto to : ch[v]) {
        //cout << v << " " << to << endl;
        if (used[to]) {
            //cout << v << " " << to << " " << root(to) << endl;
            ans += root(to);
        }
    }
    used[v] = 1;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 1; i < n; ++i) {
        //cout << i << endl;
        int p;
        cin >> p;
        g[p].push_back(i);
    }
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    int a1, a2;
    int x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    for (int i = 0; i < m; ++i) {
        //cout << a1 << " " << a2 << endl;
        ch[a1].push_back(a2);
        ch[a2].push_back(a1);
        if (a1 == a2) {
            ans += a1;
        }
        a1 = (1ll * a1 * x + 1ll * a2 * y + z) % n;
        a2 = (1ll * a2 * x + 1ll * a1 * y + z) % n;
    }
    dfs();
    cout << ans << endl;
    return 0;
}
