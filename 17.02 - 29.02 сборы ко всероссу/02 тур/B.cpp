#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long

using namespace std;

const int MAX = 50000 + 3, MAX2 = 5, ln = 16;
vector<pair<int, int>> g[MAX];
int used[MAX];
int up[5][16][MAX];
int n, k;

void dfs(int v) {
    //cout << n << " " << k << endl;
    for (int i = 0; i < ln; ++i) {
        for (int j = 0; j < k; ++j) {
            up[j][i][v] = (int)1e9;
        }
    }
    used[v] = 1;
    for (auto [to, c] : g[v]) {
        up[to % k][0][v] = c;
        if (used[to]) continue;
        dfs(to);
    }
    for (int i = 1; i < ln; ++i) {
        if ((v / k + (1 << i)) * k >= n) break;
        for (int j = 0; j < k; ++j) {
            int to = (v / k + (1 << i)) * k + j;
            if (to >= n) break;
            for (int l = 0; l < k; ++l) {
                int to2 = (v / k + (1 << (i - 1))) * k + l;
                up[j][i][v] = min(up[j][i][v], up[l][i - 1][v] + up[j][i - 1][to2]);
            }
            //cout << j << " " << i << " " << v << " " << up[i][j][v] << endl;
        }
    }
}

pair<int, int> mp[MAX];

int get(int v, int u, int ch) {
    if (v == u) return 0;
    if (v / k >= u / k) return 1e9;
    int ans = 1e9;
    for (int i = ch; i >= 0; --i) {
        if ((v / k + (1 << i)) > u / k) continue;
        for (int j = 0; j < k; ++j) {
            int to = (v / k + (1 << i)) * k + j;
            if (to > u) break;
            if (mp[to].second != u) {
                ans = min(ans, get(to, u, i) + up[j][i][v]);
            } else {
                ans = min(ans, mp[to].first + up[j][i][v]);
            }
            //cout << v << " " << to << " " << ans << " " << up[j][i][v] << endl;
        }
        break;
    }
    mp[v] = {ans, u};
    return ans;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //cout << 25 * 16 * 50000 * 4 << endl;
    int m, q;
    cin >> k >> n >> m >> q;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].push_back({b, c});
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    //cout << 0 << endl;
    for (int i = 0; i < n; ++i) {
        mp[i] = {1e9, -1};
    }
    vector<int> rans(q);
    for (int i = 0; i < q; ++i) {
        int v, u;
        cin >> v >> u;
        int ans = get(v, u, ln);
        if (ans == 1e9) {
            rans[i] = -1;
        } else {
            rans[i] = ans;
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << rans[i] << '\n';
    }
    return 0;
}
