#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

void solve1() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> wans;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        wans.push_back({u, v});
    }
    for (int i = 0; i < n + 11; ++i) {
        if (i != n) wans.push_back({n, i});
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 10; ++j) {
            if ((i >> j) & 1) {
                wans.push_back({i, n + j + 1});
            }
        }
    }
    for (int i = n + 1; i < n + 11; ++i) {
        wans.push_back({n + 11, i});
    }
    for (int i = n + 10; i >= n + 7; --i) {
        for (int j = 2 * n + 12 - i; j < i; ++j) {
            wans.push_back({i, j});
        }
    }
    wans.push_back({n + 1, n + 6});
    shuffle(wans.begin(), wans.end(), rnd);
    cout << n + 12 << " " << (int)wans.size() << endl;
    for (auto [u, v] : wans) {
        cout << u << " " << v << endl;
    }
}

void solve2() {
    int n, m;
    cin >> n >> m;
    int rn = n - 12;
    vector<int> go(n, -1);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<int> ingr;
    vector<int> tr(n);
    for (int i = 0; i < n; ++i) {
        if ((int)g[i].size() == rn + 10) {
            go[i] = rn;
        }
    }
    int only = -1;
    for (int i = 0; i < n; ++i) {
        if (go[i] == rn) continue;
        int fl = 1;
        for (int to : g[i]) {
            if (go[to] == rn) {
                fl = 0;
            }
        }
        if (fl) only = i;
    }
    assert((int)g[only].size() == 10);
    go[only] = rn + 11;
    for (int v : g[only]) {
        ingr.push_back(v);
        tr[v] = 1;
    }
    assert((int)ingr.size() == 10);
    vector<vector<int>> g2(n);
    for (int v : ingr) {
        for (int to : g[v]) {
            if (tr[to]) {
                g2[v].push_back(to);
            }
        }
    }
    int in = -1;
    for (int v : ingr) {
        if ((int)g2[v].size() > 5) {
            go[v] = rn + 2 + (int)g2[v].size();
        } else if ((int)g2[v].size() == 5) {
            int fl = 0;
            for (int to : g2[v]) {
                if ((int)g2[to].size() == 1) {
                    fl = 1;
                }
            }
            if (fl) {
                go[v] = rn + 6;
            } else {
                go[v] = rn + 7;
            }
        } else if ((int)g2[v].size() > 1) {
            go[v] = (int)g2[v].size() + rn + 1;
        } else {
            int fl = ((int)g2[g2[v][0]].size() == 8);
            if (fl) {
                go[v] = rn + 2;
            } else {
                go[v] = rn + 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int nsum = 0;
        if (go[i] != -1) continue;
        for (int to : g[i]) {
            if (go[to] <= rn) continue;
            int j = go[to] - rn - 1;
            nsum += (1 << j);
        }
        go[i] = nsum;
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; ++i) {
        for (int to : g[i]) {
            if (go[i] < rn && go[to] < rn && go[to] < go[i]) {
                ans.push_back({go[i], go[to]});
            }
        }
    }
    cout << rn << " " << (int)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}

signed main() {
    int g;
    cin >> g;
    string s;
    cin >> s;
    if (s == "Tolyatti") {
        solve1();
    } else {
        solve2();
    }
}
