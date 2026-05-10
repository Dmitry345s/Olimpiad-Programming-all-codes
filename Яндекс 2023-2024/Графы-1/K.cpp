#include<bits/stdc++.h>

using namespace std;

int MAX = 3e5;
vector<vector<int>> g(MAX), g3(MAX), g4(MAX);
vector<int> used(MAX), used2(MAX), used3(MAX), topsort;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}
void dfs2(int v) {
    used2[v] = 1;
    for (int to : g3[v]) {
        if (!used2[to]) {
            dfs2(to);
        }
    }
    topsort.push_back(v);
}

void dfs3(int v, int num) {
    used3[v] = num;
    for (int to : g4[v]) {
        if (!used3[to]) {
            dfs3(to, num);
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> g2;
    for (int i = 0; i < m; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        --a; --b;
        if (t == 2) {
            g2.push_back({a, b});
        }
        g[a].push_back(b);
    }
    dfs(0);
    for (auto [v, to] : g2) {
        if (used[v] && used[to]) {
            g3[v].push_back(to);
            g4[to].push_back(v);
        }
    }
    for (int i = 0; i < n; ++i) {
        if (!used2[i]) {
            dfs2(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    int num = 0;
    for (int v : topsort) {
        if (!used3[v]) {
            num++;
            dfs3(v, num);
        }
    }
    bool flag = false;
    for (auto [v, to] : g2) {
        if (used[v] && used[to] && used3[v] != used3[to]) {
            flag = true;
        }
    }
    if (flag) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
