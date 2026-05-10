#include<bits/stdc++.h>

using namespace std;

int MAX = 3e5 + 5, a, b;
vector<vector<int>> g(MAX), g2(MAX);
vector<pair<int, int>> crs(MAX);
vector<int> used(MAX), topsort;

void dfs0(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs0(to);
        }
    }
    topsort.push_back(v);
}

vector<int> used2(MAX);
vector<array<int, 2>> st(MAX, {(int)2e9, (int)-2e9});

void dfs2(int v, int num) {
    used2[v] = num;
    for (int to : g2[v]) {
        if (!used2[to]) {
            dfs2(to, num);
        }
    }
    if (crs[v].first == a) {
        st[num][0] = min(st[num][0], crs[v].second);
        st[num][1] = max(st[num][1], crs[v].second);
    }
}

vector<vector<int>> g3(MAX);
vector<array<int, 2>> dp(MAX, {(int)2e9, (int)-2e9});
vector<int> used3(MAX);

void dfs3(int v) {
    used3[v] = 1;
    dp[v] = st[v];
    for (int to : g3[v]) {
        if (!used3[to]) {
            dfs3(to);
        }
        dp[v][0] = min(dp[v][0], dp[to][0]);
        dp[v][1] = max(dp[v][1], dp[to][1]);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m >> a >> b;
    for (int i = 0; i < n; ++i) {
        cin >> crs[i].first >> crs[i].second;
    }
    for (int i = 0; i < m; ++i) {
        int u, v, t;
        cin >> u >> v >> t;
        --u; --v; --t;
        g[u].push_back(v);
        g2[v].push_back(u);
        if (t) {
            g[v].push_back(u);
            g2[u].push_back(v);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (crs[i].first == 0 && !used[i]) {
            dfs0(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    vector<int> f;
    for (int i = 0; i < n; ++i) {
        if (crs[i].first == a && used[i]) {
            f.push_back(crs[i].second);
        }
    }
    sort(f.begin(), f.end());
    int num = 0;
    for (int i = 0; i < (int)topsort.size(); ++i) {
        int v = topsort[i];
        if (!used2[v]) {
            num++;
            dfs2(v, num);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (used2[i] && used2[to] && used2[i] != used2[to]) {
                g3[used2[i]].push_back(used2[to]);
            }
        }
    }
    for (int i = 1; i <= num; ++i) {
        if (!used3[i]) {
            dfs3(i);
        }
    }
    vector<pair<int, int>> fans;
    for (int i = 0; i < n; ++i) {
        if (crs[i].first == 0) {
            int l = lower_bound(f.begin(), f.end(), dp[used2[i]][0]) - f.begin();
            int r = upper_bound(f.begin(), f.end(), dp[used2[i]][1]) - f.begin();
            int sz = max(r - l, 0);
            fans.push_back({crs[i].second, sz});
        }
    }
    sort(fans.rbegin(), fans.rend());
    for (int i = 0; i < (int)fans.size(); ++i) {
        cout << fans[i].second << endl;
    }
    return 0;
}
