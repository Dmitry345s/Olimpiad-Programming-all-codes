#include<bits/stdc++.h>

using namespace std;

const int MAX = 400;
vector<int> g[MAX];
int pr[MAX];
vector<int> used(MAX);

bool try_kuhn(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (pr[to] == -1) {
            pr[to] = v;
            return true;
        }
    }
    for (int to : g[v]) {
        if (used[pr[to]]) continue;
        if (try_kuhn(pr[to])) {
            pr[to] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> f(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    int l = 0, r = 1e9 + 1;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            for (int j = 0; j < m; ++j) {
                pr[j + n] = -1;
                if (f[i][j] >= c) {
                    g[i].push_back(j + n);
                }
            }
        }
        int ch = 0;
        for (int i = 0; i < n; ++i) {
            used.assign(n + m, 0);
            ch += try_kuhn(i);
        }
        if (ch == min(n, m)) {
            l = c;
        } else {
            r = c;
        }
    }
    cout << l << endl;
    return 0;
}
