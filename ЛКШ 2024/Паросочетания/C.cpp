#include<bits/stdc++.h>

using namespace std;

int MAX = 500;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
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

vector<vector<int>> g_last(MAX);
vector<int> used_last(MAX);

void dfs(int v) {
    used_last[v] = 1;
    for (int to : g_last[v]) {
        if (used_last[to]) continue;
        dfs(to);
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    int u, v;
    vector<vector<int>> g2(max(n, m));
    while (cin >> v >> u) {
        --v; --u;
        g[v].push_back(u);
        g2[u].push_back(v);
    }
    for (int i = 0; i < n; ++i) {
        if (try_kuhn(i)) {
            timer++;
        }
    }
    for (int i = 0; i < m; ++i) {
        for (int to : g2[i]) {
            if (now_pair[i] != to) {
                g_last[i + n].push_back(to);
            } else {
                g_last[to].push_back(i + n);
            }
        }
    }
    for (int i = 0; i < m; ++i) {
        if (now_pair[i] == -1) {
            dfs(i + n);
        }
    }
    vector<int> ans1, ans2;
    for (int i = 0; i < n; ++i) {
        if (used_last[i]) {
            ans1.push_back(i);
        }
    }
    for (int i = n; i < n + m; ++i) {
        if (!used_last[i]) {
            ans2.push_back(i - n);
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
    return 0;
}
