#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5, LN = 19;
vector<vector<int>> g(MAX);
vector<vector<int>> cd(MAX, vector<int> (LN, -1));
vector<int> used(MAX, -1), sz(MAX);

void f_c(int v, int p, int t_sz, int & cent) {
    if (t_sz == 1) {
        cent = v;
        return;
    }
    sz[v] = 1;
    int mx_sz = 0;
    for (int to : g[v]) {
        if (to == p || used[to] != -1) continue;
        f_c(to, v, t_sz, cent);
        sz[v] += sz[to];
        mx_sz = max(mx_sz, sz[to]);
    }
    //cout << v << " " << t_sz << " " << sz[v] << endl;
    mx_sz = max(mx_sz, t_sz - sz[v]);
    if (mx_sz <= t_sz / 2) {
        cent = v;
    }
}

void dfs(int v, int p, int num, int st) {
    cd[v][num] = st;
    for (int to : g[v]) {
        if (to == p || used[to] != -1) continue;
        dfs(to, v, num, st);
    }
}

void solve(int v, int num, int t_sz) {
    //cout << v << endl;
    int cent;
    f_c(v, -1, t_sz, cent);
    //cout << cent << endl;
    used[cent] = num;
    dfs(cent, -1, num, cent);
    for (int to : g[cent]) {
        if (used[to] == -1) {
            int sz_to = sz[to];
            if (sz_to > sz[cent]) {
                sz_to = t_sz - sz[cent];
            }
            solve(to, num + 1, sz_to);
        }
    }
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
    solve(0, 1, n);
    //cout << 1 << endl;
    for (int i = 0; i < n; ++i) {
        cout << cd[i][used[i] - 1] + 1 << " ";
    }
    cout << endl;
    return 0;
}
