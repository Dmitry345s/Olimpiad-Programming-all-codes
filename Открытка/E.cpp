#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<vector<pair<int, int>>> g(MAX);
vector<int> used(MAX), cl(MAX);

void dfs(int v) {
    used[v] = 1;
    for (auto [to, i] : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}

vector<int> used2(MAX), used3(MAX);
vector<vector<int>> g2(MAX);
int ans = 1;

void dfs2(int v, int p) {
    used2[v] = 0;
    used3[v] = 1;
    for (int to : g2[v]) {
        if (to == p) continue;
        if (used3[to]) {
            ans = 0;
        } else {
            dfs2(to, v);
        }
    }
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<set<int>> u(k + 1);
    vector<pair<int, int>> eds(m);
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
        cl[i] = c;
        u[c].insert(i);
        eds[i] = {a, b};
    }
    int ch = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            dfs(i);
            ch++;
        }
    }
    int q;
    cin >> q;
    for (int _ = 0; _ < q; ++_) {
        int e, w;
        cin >> e >> w;
        --e;
        u[cl[e]].erase(e);
        cl[e] = w;
        u[cl[e]].insert(e);
        if (ch > 1) {
            cout << "No" << endl;
            continue;
        }
        int rans = 0;
        for (int i = 1; i <= k; ++i) {
            if (u[i].size() == 0) {
                rans = 1;
            }
        }
        //cout << _ << " " << rans << endl;
        if (rans == 1) {
            cout << "No" << endl;
            continue;
        }
        for (int i = 0; i < (1 << k); ++i) {
            set<int> st;
            for (int j = 0; j < k; ++j) {
                if (u[j + 1].size() > 2) continue;
                auto it = u[j + 1].begin();
                if (u[j + 1].size() == 2 && ((i >> j) & 1)) {
                    it++;
                }
                auto [v, to] = eds[*it];
                st.insert(v);
                st.insert(to);
                if (!used2[v]) {
                    g2[v].clear();
                    used2[v] = 1;
                    used3[v] = 0;
                }
                if (!used2[to]) {
                    g2[to].clear();
                    used2[to] = 1;
                    used3[to] = 0;
                }
                g2[v].push_back(to);
                g2[to].push_back(v);
            }
            ans = 1;
            for (auto v : st) {
                if (!used3[v]) {
                    dfs2(v, -1);
                }
            }
            rans |= ans;
        }
        if (rans) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
