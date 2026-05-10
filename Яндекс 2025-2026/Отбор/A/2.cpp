#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5;
int r[MAX];
vector<pair<int, int>> g[MAX];
int used[MAX], sz[MAX];

void find_c(int v, int n, int p, int & c) {
    sz[v] = 1;
    int mx = 0;
    for (auto [to, t] : g[v]) {
        if (used[to] || to == p) continue;
        find_c(to, n, v, c);
        sz[v] += sz[to];
        mx = max(mx, sz[to]);
    }
    mx = max(mx, n - sz[v]);
    if (mx <= n / 2) {
        c = v;
    }
}

vector<pair<int, int>> now1;

void dfs1(int v, int p, int mn, int sm) {
    now1.push_back({mn, sm});
    for (auto [to, t] : g[v]) {
        if (to == p || used[to]) continue;
        dfs1(to, v, min(mn + r[to] - t, r[to] - t), sm + r[to] - t);
    }
}

vector<pair<int, int>> now2;

void dfs2(int v, int p, int mn, int sm) {
    now2.push_back({mn, sm});
    for (auto [to, t] : g[v]) {
        if (to == p || used[to]) continue;
        dfs2(to, v, min(mn, sm - t), sm + r[to] - t);
    }
}

int ans = 0;

void solve(int v, int nsz) {
    int c;
    find_c(v, nsz, v, c);
    vector<vector<pair<int, int>>> d1;
    vector<vector<pair<int, int>>> d2;
    vector<pair<int, int>> alld2;
    for (auto [to, t] : g[c]) {
        if (used[to]) continue;
        now1.clear();
        dfs1(to, c, r[to] - t, r[c] + r[to] - t);
        //now1.erase(now1.begin());
        d1.push_back(now1);
    }
    for (auto [to, t] : g[c]) {
        if (used[to]) continue;
        now2.clear();
        dfs2(to, c, -t, r[to] - t);
        d2.push_back(now2);
        for (auto u : now2) {
            alld2.push_back(u);
        }
        sort(d2.back().begin(), d2.back().end());
    }
    sort(alld2.begin(), alld2.end());
    for (int i = 0; i < (int)d1.size(); ++i) {
        for (auto [mn, sm] : d1[i]) {
            if (mn < 0) continue;
            if (sm > 0) ans += 1;
            int j1 = (int)alld2.size() - (lower_bound(alld2.begin(), alld2.end(), pair<int, int>{-sm, -sm + 1}) - alld2.begin());
            int j2 = (int)d2[i].size() - (lower_bound(d2[i].begin(), d2[i].end(), pair<int, int>{-sm, -sm + 1}) - d2[i].begin());
            ans += j1 - j2;
        }
    }
    ans += (int)alld2.size() - (lower_bound(alld2.begin(), alld2.end(), pair<int, int>{-r[c], -r[c] + 1}) - alld2.begin());
    used[c] = 1;
    for (auto [to, t] : g[c]) {
        if (used[to]) continue;
        if (sz[to] > sz[c]) {
            solve(to, nsz - sz[c]);
        } else {
            solve(to, sz[to]);
        }
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        --a; --b;
        g[a].push_back({b, t});
        g[b].push_back({a, t});
    }
    solve(0, n);
    cout << ans << endl;
    return 0;
}
