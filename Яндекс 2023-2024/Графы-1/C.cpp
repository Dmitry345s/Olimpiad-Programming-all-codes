#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<vector<int>> g(MAX), g2(MAX);
vector<int> used(MAX), used2(MAX), topsort;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    topsort.push_back(v);
}

void dfs2(int v, int num) {
    used2[v] = num;
    for (int to : g2[v]) {
        if (!used2[to]) {
            dfs2(to, num);
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
    int num = 0;
    for (int i = 0; i < n; ++i) {
        int v = topsort[i];
        if (!used2[v]) {
            num++;
            dfs2(v, num);
        }
    }
    cout << num << endl;
    for (int i = 0; i < n; ++i) {
        cout << used2[i] << " ";
    }
    return 0;
}
