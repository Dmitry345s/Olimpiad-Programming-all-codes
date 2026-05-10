#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<vector<int>> g(MAX), g2(MAX);
vector<int> used(MAX), used2(MAX), topsort;
int ncnt = 0;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    topsort.push_back(v);
}

void dfs2(int v) {
    ncnt += 1;
    used2[v] = 1;
    for (int to : g2[v]) {
        if (!used2[to]) {
            dfs2(to);
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g2[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    reverse(topsort.begin(), topsort.end());
    int cnt = 0;
    for (int v : topsort) {
        if (!used2[v]) {
            ncnt = 0;
            dfs2(v);
            cnt += min(ncnt, 2);
        }
    }
    cout << cnt << endl;
    return 0;
}
