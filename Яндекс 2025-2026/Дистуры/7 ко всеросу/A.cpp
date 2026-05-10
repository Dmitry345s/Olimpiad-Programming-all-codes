#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5, INF = 2e9;
int l[MAX], r[MAX];
vector<int> g[MAX];
pair<int, int> dp[MAX];
set<pair<int, int>> alll[MAX];
set<pair<int, int>> allr[MAX];

void dfs(int v, int p) {
    alll[v].insert({1, -1});
    allr[v].insert({INF, -1});
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        alll[v].insert({-dp[to].first, to});
        allr[v].insert({dp[to].second, to});
    }
    dp[v].first = -alll[v].begin()->first;
    dp[v].second = allr[v].begin()->first;
    if (dp[v].first > dp[v].second) {
        dp[v].first = INF;
        dp[v].second = 0;
        return;
    }
    if (v != p && (int)g[v].size() == 1) {
        dp[v] = {l[v], r[v]};
    } else {
        dp[v].first += l[v];
        dp[v].second += r[v];
    }
}

int ans[MAX];

void solve(int v, int p) {
    if (dp[v].first <= dp[v].second) {
        ans[v] = 1;
    }
    for (int to : g[v]) {
        if (to == p) continue;
        alll[v].erase({-dp[to].first, to});
        allr[v].erase({dp[to].second, to});
        dp[v].first = -alll[v].begin()->first;
        dp[v].second = allr[v].begin()->first;
        if (dp[v].first > dp[v].second) {
            dp[v].first = INF;
            dp[v].second = 0;
        } else if ((int)g[v].size() == 1) {
            dp[v] = {l[v], r[v]};
        } else {
            dp[v].first += l[v];
            dp[v].second += r[v];
        }
        alll[to].insert({-dp[v].first, v});
        allr[to].insert({dp[v].second, v});
        dp[to].first = -alll[to].begin()->first;
        dp[to].second = allr[to].begin()->first;
        if (dp[to].first > dp[to].second) {
            dp[to].first = INF;
            dp[to].second = 0;
        } else {
            dp[to].first += l[to];
            dp[to].second += r[to];
        }
        solve(to, v);
        alll[to].erase({-dp[v].first, v});
        allr[to].erase({dp[v].second, v});
        dp[to].first = -alll[to].begin()->first;
        dp[to].second = allr[to].begin()->first;
        if (dp[to].first > dp[to].second) {
            dp[to].first = INF;
            dp[to].second = 0;
        } else if ((int)g[to].size() == 1) {
            dp[to] = {l[to], r[to]};
        } else {
            dp[to].first += l[to];
            dp[to].second += r[to];
        }
        alll[v].insert({-dp[to].first, to});
        allr[v].insert({dp[to].second, to});
        dp[v].first = -alll[v].begin()->first;
        dp[v].second = allr[v].begin()->first;
        if (dp[v].first > dp[v].second) {
            dp[v].first = INF;
            dp[v].second = 0;
        } else {
            dp[v].first += l[v];
            dp[v].second += r[v];
        }
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
    }
    dfs(0, 0);
    solve(0, 0);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
