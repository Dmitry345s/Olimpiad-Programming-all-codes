#include<bits/stdc++.h>
//#pragma GCC optimize("O3")
//#pragma GCC optimize("unroll-loops")

using namespace std;

vector<vector<int>> g, g2, g3;

void getg(vector<array<int, 3>> b, int m) {
    sort(b.begin(), b.end());
    for (int i = 1; i < (int)b.size(); ++i) {
        int v = b[i][1] * m + b[i][2];
        int to = b[i - 1][1] * m + b[i - 1][2];
        g[v].push_back(to);
        g2[to].push_back(v);
        if (b[i][0] == b[i - 1][0]) {
            g[to].push_back(v);
            g2[v].push_back(to);
        }
    }
}

int MAX = 1e6 + 5;
vector<int> used(MAX), topsort;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    topsort.push_back(v);
}

vector<int> used2(MAX);

void dfs2(int v, int num) {
    used2[v] = num;
    for (int to : g2[v]) {
        if (!used2[to]) {
            dfs2(to, num);
        }
    }
}

vector<int> used3(MAX), dp(MAX);

void dfs3(int v, int p) {
    used3[v] = 1;
    dp[v] = 1;
    for (int to : g3[v]) {
        if (to == p) continue;
        if (!used3[to]) {
            dfs3(to, v);
        }
        dp[v] = max(dp[v], dp[to] + 1);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    g.resize(n * m + 5);
    g2.resize(n * m + 5);
    vector<vector<int>> a(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        vector<array<int, 3>> toget;
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            toget.push_back({a[i][j], i, j});
        }
        getg(toget, m);
        toget.clear();
    }
    for (int j = 0; j < m; ++j) {
        vector<array<int, 3>> toget;
        for (int i = 0; i < n; ++i) {
            toget.push_back({a[i][j], i, j});
        }
        getg(toget, m);
        toget.clear();
    }
    for (int i = 0; i < n * m; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    int num = 0;
    for (int i = 0; i < n * m; ++i) {
        int v = topsort[i];
        if (!used2[v]) {
            num++;
            dfs2(v, num);
        }
    }
    g2.clear();
    set<pair<int, int>> st;
    g3.resize(num + 1);
    for (int i = 0; i < n * m; ++i) {
        for (int to : g[i]) {
            if (used2[to] != used2[i]) {
                g3[used2[i]].push_back(used2[to]);
            }
        }
    }
    g.clear();
    for (int i = 1; i < num + 1; ++i) {
        if (!used3[i]) {
            dfs3(i, i);
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int v = i * m + j;
            cout << dp[used2[v]] << " ";
        }
        cout << '\n';
    }
}
