#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5, LN = 19, INF = 2e9;
vector<vector<pair<int, int>>> g(MAX);
vector<int> sz(MAX), used(MAX, -1);

void f_c(int v, int p, int t_sz, int & cent) {
    //cout << v << " " << t_sz << endl;
    int mx_sz = 0;
    sz[v] = 1;
    for (auto [to, len] : g[v]) {
        if (to == p || used[to] != -1) continue;
        f_c(to, v, t_sz, cent);
        sz[v] += sz[to];
        mx_sz = max(mx_sz, sz[to]);
    }
    mx_sz = max(mx_sz, t_sz - sz[v]);
    if (mx_sz <= t_sz / 2) {
        cent = v;
    }
}

vector<vector<int>> cd(MAX, vector<int> (LN, -1));
vector<vector<int>> d_len(MAX, vector<int> (LN, 0));
vector<set<pair<int, int>>> all(MAX);

void dfs(int v, int p, int del, int num, int now) {
    //cout << v << " " << p << endl;
    cd[v][num] = now;
    d_len[v][num] = d_len[p][num] + del;
    for (auto [to, len] : g[v]) {
        if (to == p || used[to] != -1) continue;
        dfs(to, v, len, num, now);
    }
}

void solve(int v, int num, int t_sz) {
    //cout << v << endl;
    int cent;
    f_c(v, -1, t_sz, cent);
    //cout << cent << endl;
    used[cent] = num;
    dfs(cent, cent, 0, num, cent);
    for (auto [to, c] : g[cent]) {
        if (used[to] == -1) {
            int sz_to = sz[to];
            if (sz_to > sz[cent]) {
                sz_to = t_sz - sz[cent];
            }
            solve(to, num + 1, sz_to);
        }
    }
}

void del(int v) {
    for (int i = 0; i < LN; ++i) {
        if (cd[v][i] == -1) break;
        all[cd[v][i]].erase({d_len[v][i], v});
    }
}

void add(int v) {
    for (int i = 0; i < LN; ++i) {
        if (cd[v][i] == -1) break;
        all[cd[v][i]].insert({d_len[v][i], v});
    }
}

int get(int v) {
    int ans = INF;
    for (int i = 0; i < LN; ++i) {
        if (cd[v][i] == -1) break;
        //cout << ans << " " << i << endl;
        if ((int)all[cd[v][i]].size() >= 1) {
            ans = min(ans, (*all[cd[v][i]].begin()).first + d_len[v][i]);
        }
        //cout << ans << " " << i << endl;
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v, l;
        cin >> u >> v >> l;
        --u; --v;
        g[u].push_back({v, l});
        g[v].push_back({u, l});
    }
    solve(0, 0, n);
    add(0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        if (t == '-') {
            int v;
            cin >> v;
            --v;
            del(v);
        } else if (t == '+') {
            int v;
            cin >> v;
            --v;
            add(v);
        } else {
            int v;
            cin >> v;
            --v;
            cout << get(v) << endl;
        }
    }
    return 0;
}
