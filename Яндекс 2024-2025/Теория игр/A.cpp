#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 1;
vector<int> g[MAX];
int used[MAX], deg[MAX];

void dfs(int v, int t) {
    used[v] = t;
    if (t == -1) {
        for (int to : g[v]) {
            if (!used[to]) {
                dfs(to, 1);
            }
        }
    } else {
        for (int to : g[v]) {
            if (!used[to] && !(--deg[to])) {
                dfs(to, -1);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) {
            deg[i] = 0;
            used[i] = 0;
            g[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            deg[a]++;
            g[b].push_back(a);
        }
        for (int i = 0; i < n; ++i) {
            if (deg[i] == 0 && !used[i]) {
                dfs(i, -1);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (used[i] == -1) {
                cout << "SECOND" << '\n';
            } else if (used[i] == 1) {
                cout << "FIRST" << '\n';
            } else {
                cout << "DRAW" << '\n';
            }
        }
        cout << '\n';
    }
    return 0;
}
