#include<bits/stdc++.h>

using namespace std;

int MAX = 5e5;
vector<vector<int>> g(MAX), g2(MAX);
vector<int> used(MAX);
int flag = 1;

void dfs(int v) {
    used[v] = -1;
    for (int to : g[v]) {
        if (used[to] == -1) {
            flag = 0;
            return;
        }
        if (used[to] == 0) {
            dfs(to);
        }
    }
    used[v] = 1;
}

vector<int> h(MAX), used2(MAX);

void dfs2(int v) {
    used2[v] = 1;
    for (int to : g2[v]) {
        if (!used2[to]) {
            dfs2(to);
        }
        h[v] = max(h[v], h[to] + 1);
    }
}

int flag2 = 1;
vector<int> ans(MAX), used3(MAX);
vector<vector<int>> g3(MAX);

void dfs3(int v, int p = -2) {
    used3[v] = 1;
    ans[v] = p;
    if (p != -2) {
        g3[p].push_back(v);
    }
    for (int to : g[v]) {
        if (h[v] + 1 != h[to]) continue;
        if (used3[to]) {
            flag2 = 0;
            return;
        } else {
            dfs3(to, v);
        }
    }
}

vector<set<int>> g4(MAX);
int flag3 = 1;

void dfs4(int v) {
    int maxm = 0;
    int in = -1;
    g4[v] = {v};
    for (int to : g3[v]) {
        if (ans[v] == to) continue;
        dfs4(to);
        if (g4[to].size() >= maxm) {
            maxm = g4[to].size();
            in = to;
        }
    }
    if (in != -1) {
        swap(g4[v], g4[in]);
        for (int to : g3[v]) {
            if (ans[v] == to) continue;
            while (!g4[to].empty()) {
                int k = (*g4[to].begin());
                g4[v].insert(k);
                g4[to].erase(g4[to].begin());
            }
        }
    }
    for (int to : g[v]) {
        if (g4[v].find(to) == g4[v].end()) {
            flag3 = 0;
            return;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> cnt(n);
    vector<set<int>> ch(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (ch[a].find(b) != ch[a].end()) continue;
        g[a].push_back(b);
        g2[b].push_back(a);
        ch[a].insert(b);
        cnt[b]++;
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == 0) {
            dfs(i);
        }
    }
    if (flag == 0) {
        cout << "No" << endl;
        return 0;
    }
    int st = -1;
    for (int i = 0; i < n; ++i) {
        if (cnt[i] == 0) {
            if (st != -1) {
                cout << "No" << endl;
                return 0;
            }
            st = i;
        }
    }
    if (st == -1) {
        cout << "No" << endl;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (!used2[i]) {
            dfs2(i);
        }
    }
    dfs3(st);
    if (flag2 == 0) {
        cout << "No" << endl;
        return 0;
    }
    dfs4(st);
    if (flag3 == 0) {
        cout << "No" << endl;
        return 0;
    }
    cout << "Yes" << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
