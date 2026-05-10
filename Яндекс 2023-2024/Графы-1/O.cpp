#include<bits/stdc++.h>

using namespace std;

struct edge {
    int to, i;
};

int MAX = 1e5 + 10;
vector<vector<edge>> g(MAX);
vector<int> used(MAX), h(MAX), c(MAX);
vector<pair<int, int>> start(MAX), fin(MAX, {-1, -1});

void dfs(int v) {
    used[v] = 1;
    for (auto [to, i] : g[v]) {
        if (fin[i] == pair<int, int>{-1, -1} && c[v] == c[to]) {
            fin[i] = {v, to};
        }
        if (used[to] || c[v] != c[to]) continue;
        dfs(to);
    }
}
signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        start[i] = {a, b};
    }
    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < m; ++i) {
        auto [v, to] = start[i];
        if (c[v] > c[to]) {
            cout << "->" << endl;
        } else if (c[v] < c[to]) {
            cout << "<-" << endl;
        } else if (start[i] == fin[i]) {
            cout << "->" << endl;
        } else {
            cout << "<-" << endl;
        }
    }
    return 0;
}
