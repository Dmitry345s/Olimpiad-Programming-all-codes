#include<bits/stdc++.h>

using namespace std;

const int MOD = 12289;

int pows[MOD];
int used[MOD];
int fl = 0;
int used2[MOD];

void dfs(int v, vector<vector<int>> & g) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used2[to]) continue;
        if (used[to] == 1) {
            fl = 1;
            return;
        }
        if (used[to]) continue;
        dfs(to, g);
    }
    used[v] = 2;
}

signed main() {
    int n, k;
    cin >> n >> k;
    pows[0] = 1;
    for (int i = 1; i < MOD; ++i) {
        pows[i] = pows[i - 1] * 2;
    }
    vector<pair<int, int>> all;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j) all.push_back({i, j});
        }
    }
    int ans = 0;
    for (int mask = 0; mask < pows[(int)all.size()]; ++mask) {
        vector<vector<int>> g(n);
        fl = 0;
        for (int bit = 0; bit < (int)all.size(); ++bit) {
            int nb = (mask >> bit) % 2;
            if (nb) {
                g[all[bit].first].push_back(all[bit].second);
            }
        }
        for (int _ = 0; _ < n; ++_) {
            vector<pair<int, int>> now;
            for (int i = 0; i < n; ++i) {
                for (int to : g[i]) {
                    for (int to2 : g[to]) {
                        if (i != to2) now.push_back({i, to2});
                    }
                }
            }
            for (auto [v, v2] : now) {
                g[v].push_back(v2);
            }
        }
        int mx = 0;
        for (int i = 0; i < (1 << n); ++i) {
            fill(used2, used2 + n, 0);
            fill(used, used + n, 0);
            fl = 0;
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                used2[j] = (i >> j) % 2;
                cnt += used2[j];
            }
            for (int j = 0; j < n; ++j) {
                if (used2[j] && !used[j]) {
                    dfs(j, g);
                }
            }
            if (!fl) {
                mx = max(mx, cnt);
            }
        }
        if (mx == k) {
            ans++;
        }
    }
    cout << ans % MOD << endl;
    return 0;
}
