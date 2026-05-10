#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));
const int MAX = 5e5 + 1;
vector<int> g[MAX];
int used[MAX];
int flag = 0;

void dfs(int v, int p) {
    if (p == -1) {
        used[v] = 0;
    } else {
        used[v] = (used[p] ^ 1);
    }
    for (int to : g[v]) {
        if (to == p) continue;
        if (used[to] != -1) {
            if (used[to] != used[v]) {
                flag = 1;
                return;
            }
            continue;
        }
        dfs(to, v);
        if (flag) return;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; ++i) {
            g[i].clear();
        }
        for (int i = 0; i < m; ++i) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        vector<int> all(n);
        for (int i = 0; i < n; ++i) {
            all[i] = i;
        }
        int ans = 0;
        for (int _ = 0; _ < 15; ++_) {
            shuffle(all.begin(), all.end(), rnd);
            for (int i = 0; i < n; ++i) {
                shuffle(g[i].begin(), g[i].end(), rnd);
            }
            fill(used, used + n, -1);
            flag = 0;
            for (int i = 0; i < n; ++i) {
                if (used[all[i]] == -1) {
                    dfs(all[i], -1);
                    if (flag) break;
                }
            }
            ans |= flag;
            if (ans) break;
        }
        if (ans) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
