#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5, MAX2 = 1e6 + 5, INF = 1e9;
vector<vector<pair<int, int>>> g(MAX);
vector<int> sz(MAX), used(MAX, -1);
int k;

void f_c(int v, int p, int t_sz, int & cent) {
    sz[v] = 1;
    int mx = 0;
    for (auto [to, len] : g[v]) {
        if (to == p || used[to] != -1) continue;
        f_c(to, v, t_sz, cent);
        sz[v] += sz[to];
        mx = max(mx, sz[to]);
    }
    mx = max(mx, t_sz - sz[v]);
    if (mx <= t_sz / 2) {
        cent = v;
    }
}

int ch[MAX2];
vector<int> all2;
vector<pair<int, int>> all;
int ans = INF;

void dfs(int v, int p, int now, int last, int last2) {
    if (v == now) {
        ch[last] = min(ch[last], last2);
    }
    all.push_back({last, last2});
    all2.push_back(last);
    if (last <= k) {
        ans = min(ans, ch[k - last] + last2);
    }
    for (auto [to, len] : g[v]) {
        if (to == p || used[to] != -1) continue;
        dfs(to, v, now, last + len, last2 + 1);
        if (v == now) {
            for (auto [dist, len] : all) {
                if (dist <= k) {
                    ch[dist] = min(ch[dist], len);
                }
            }
            all.clear();
        }
    }
}

void solve(int v, int num, int t_sz) {
    int cent;
    f_c(v, -1, t_sz, cent);
    used[cent] = num;
    dfs(cent, cent, cent, 0, 0);
    for (int num : all2) {
        if (num >= k) continue;
        ch[num] = INF;
    }
    all2.clear();
    for (auto [to, len] : g[cent]) {
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
    cin >> n >> k;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, l;
        cin >> a >> b >> l;
        g[a].push_back({b, l});
        g[b].push_back({a, l});
    }
    for (int i = 0; i < MAX2; ++i) {
        ch[i] = INF;
    }
    solve(0, 0, n);
    if (ans == INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
