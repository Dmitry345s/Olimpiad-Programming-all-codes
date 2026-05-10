#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<vector<int>> g(MAX);
vector<int> used(MAX), topsort;
bool flag = true;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to] == 2) continue;
        if (used[to]) flag = false;
        if (!used[to]) {
            dfs(to);
        }
    }
    used[v] = 2;
    topsort.push_back(v);
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
        }
    }
    if (!flag) {
        cout << -1 << endl;
        return 0;
    }
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < n; ++i) {
        cout << topsort[i] + 1 << " ";
    }
    return 0;
}
