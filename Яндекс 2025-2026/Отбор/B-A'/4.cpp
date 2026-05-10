#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5 + 1;
vector<int> g[MAX];
int used[MAX];
int fl = 1;

void dfs(int v, int num) {
    used[v] = ((num - 1) ^ 1) + 1;
    for (int to : g[v]) {
        if (used[to]) {
            if (used[to] == used[v]) {
                fl = 0;
            }
            continue;
        }
        dfs(to, used[v]);
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<array<int, 3>> ed;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        ed.push_back({c, a, b});
    }
    ed.push_back({(int)2e9, -1, -1});
    sort(ed.begin(), ed.end());
    int l = 0, r = m + 1;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        fill(used, used + n, 0);
        fl = 1;
        for (int i = 0; i < c; ++i) {
            auto [c, a, b] = ed[i];
            g[a].push_back(b);
            g[b].push_back(a);
        }
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                dfs(i, 2);
            }
        }
        if (fl) {
            l = c;
        } else {
            r = c;
        }
    }
    //cout << l << endl;
    for (int i = 0; i < n; ++i) {
        g[i].clear();
    }
    for (int i = 0; i < l; ++i) {
        auto [c, a, b] = ed[i];
        g[a].push_back(c);
        g[b].push_back(c);
    }
    int cnt = (int)2e9;
    for (int i = 0; i < n; ++i) {
        sort(g[i].begin(), g[i].end());
        if ((int)g[i].size() >= 2) {
            cnt = min(cnt, g[i][0] + g[i][1]);
        }
    }
    cout << min(ed[l][0], cnt) << endl;
    return 0;
}
