#include<bits/stdc++.h>

using namespace std;

int MAX = 500;
vector<vector<int>> g(MAX), g2(MAX), g_last(MAX);
vector<int> used(MAX), used_last(MAX);
vector<int> now_pair(MAX, -1);
int timer = 1;

bool try_kuhn(int v) {
    if (used[v] == timer) return 0;
    used[v] = timer;
    for (int to : g[v]) {
        if (now_pair[to] == -1 || try_kuhn(now_pair[to])) {
            now_pair[to] = v;
            return 1;
        }
    }
    return 0;
}

void dfs(int v) {
    used_last[v] = 1;
    for (int to : g_last[v]) {
        if (used_last[to]) continue;
        dfs(to);
    }
}

signed main() {
    int k;
    cin >> k;
    while (k--) {
        int n, m;
        cin >> m >> n;
        vector<vector<int>> to_edges(m, vector<int> (n, 1));
        for (int i = 0; i < m; ++i) {
            int now;
            cin >> now;
            while (now) {
                --now;
                to_edges[i][now] = 0;
                cin >> now;
            }
        }
        for (int i = 0; i < m; ++i) {
            g[i].clear();
            g_last[i].clear();
            used_last[i] = 0;
            used[i] = 0;
        }
        for (int j = 0; j < n; ++j) {
            g2[j].clear();
            g_last[j + m].clear();
            used_last[j + m] = 0;
            now_pair[j] = -1;
        }
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (to_edges[i][j]) {
                    //cout << i << " " << j << endl;
                    g[i].push_back(j);
                    g2[j].push_back(i);
                }
            }
        }
        timer = 1;
        for (int i = 0; i < m; ++i) {
            if (try_kuhn(i)) {
                timer++;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int to : g2[i]) {
                if (now_pair[i] != to) {
                    g_last[i + m].push_back(to);
                } else {
                    g_last[to].push_back(i + m);
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            if (now_pair[i] == -1) {
                dfs(i + m);
            }
        }
        vector<int> ans1, ans2;
        for (int i = 0; i < m; ++i) {
            if (!used_last[i]) {
                ans1.push_back(i);
            }
        }
        for (int i = 0; i < n; ++i) {
            if (used_last[i + m]) {
                ans2.push_back(i);
            }
        }
        cout << (int)ans1.size() + (int)ans2.size() << endl;
        cout << (int)ans1.size() << " " << (int)ans2.size() << endl;
        for (int i = 0; i < (int)ans1.size(); ++i) {
            cout << ans1[i] + 1 << " ";
        }
        cout << endl;
        for (int i = 0; i < (int)ans2.size(); ++i) {
            cout << ans2[i] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
