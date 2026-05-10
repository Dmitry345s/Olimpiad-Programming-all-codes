#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5;
vector<int> g[MAX];
vector<int> gt[MAX];
int cnt[MAX];
int ans[MAX];

signed main() {
    freopen("retro.in", "r", stdin);
    freopen("retro.out", "w", stdout);
    int n, m;
    while (cin >> n >> m) {
        for (int i = 0; i < n; ++i) {
            g[i].clear();
            gt[i].clear();
            cnt[i] = 0;
            ans[i] = 0;
        }
        for (int i = 0; i < m; ++i) {
            int u, v;
            cin >> u >> v;
            --u; --v;
            g[u].push_back(v);
            gt[v].push_back(u);
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            cnt[i] = (int)g[i].size();
            if (cnt[i] == 0) {
                q.push(i);
                ans[i] = -1;
            }
        }
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int to : gt[v]) {
                if (ans[to] != 0) continue;
                cnt[to]--;
                if (ans[v] == -1) {
                    q.push(to);
                    ans[to] = 1;
                    continue;
                }
                if (cnt[to] == 0) {
                    q.push(to);
                    ans[to] = -1;
                    continue;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (ans[i] == -1) {
                cout << "SECOND" << endl;
            } else if (ans[i] == 1) {
                cout << "FIRST" << endl;
            } else {
                cout << "DRAW" << endl;
            }
        }
    }
    return 0;
}
