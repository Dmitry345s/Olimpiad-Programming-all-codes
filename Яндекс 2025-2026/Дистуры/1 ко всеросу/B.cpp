#include<bits/stdc++.h>

using namespace std;

const int MAX = 4e6, C = 10;

vector<int> g[MAX];
int used[MAX];
int fl = 0;
vector<int> now;
vector<int> ans;

void dfs(int v) {
    used[v] = 1;
    now.push_back(v);
    for (int to : g[v]) {
        if (used[to] == 2) continue;
        if (used[to] == 1) {
            fl = 1;
            while (!now.empty() && now.back() != to) {
                ans.push_back(now.back());
                now.pop_back();
            }
            ans.push_back(now.back());
            return;
        }
        dfs(to);
        if (fl) return;
    }
    used[v] = 2;
    now.pop_back();
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> allt(n);
        vector<array<int, 4>> edg(m);
        for (int i = 0; i < m; ++i) {
            int a, b, c;
            cin >> a >> b >> c;
            --a; --b; --c;
            allt[a].push_back(c);
            edg[i] = {a, b, c, i};
        }
        for (int i = 0; i < n; ++i) {
            allt[i].push_back(-1);
        }
        sort(edg.begin(), edg.end());
        vector<int> st(n);
        int stnow = 0;
        for (int i = 0; i < n; ++i) {
            sort(allt[i].begin(), allt[i].end());
            allt[i].erase(unique(allt[i].begin(), allt[i].end()), allt[i].end());
            st[i] = stnow;
            stnow += (int)allt[i].size() * 2;
        }
        for (int i = 0; i < stnow; ++i) {
            g[i].clear();
            used[i] = 0;
        }
        for (int i = 0; i < n; ++i) {
            int ts = (int)allt[i].size();
            for (int j = st[i]; j < st[i] + ts - 1; ++j) {
                g[j].push_back(j + 1);
            }
            for (int j = st[i] + ts + 1; j < st[i] + 2 * ts; ++j) {
                g[j].push_back(j - 1);
            }
        }
        for (auto [a, b, c, i] : edg) {
            int u = lower_bound(allt[a].begin(), allt[a].end(), c) - allt[a].begin();
            int v1 = u + st[a];
            int v2 = u + st[a] + (int)allt[a].size();
            int y = lower_bound(allt[b].begin(), allt[b].end(), c) - allt[b].begin();
            if (y == (int)allt[b].size() || allt[b][y] != c) {
                g[v1].push_back(st[b]);
                g[v2].push_back(st[b]);
                g[v1].push_back(st[b] + 2 * (int)allt[b].size() - 1);
                g[v2].push_back(st[b] + 2 * (int)allt[b].size() - 1);
                continue;
            }
            if (y + 1 < (int)allt[b].size()) {
                int v3 = st[b] + y + 1;
                g[v1].push_back(v3);
                g[v2].push_back(v3);
            }
            if (y - 1 >= 0) {
                int v4 = st[b] + y - 1 + (int)allt[b].size();
                g[v1].push_back(v4);
                g[v2].push_back(v4);
            }
        }
        fl = 0;
        for (int i = 0; i < stnow; ++i) {
            if (!used[i]) {
                now.clear();
                ans.clear();
                dfs(i);
                if (fl) break;
            }
        }
        if (!fl) {
            cout << "NO" << endl;
        } else {
            reverse(ans.begin(), ans.end());
            vector<pair<int, int>> mrans;
            for (int i = 0; i < (int)ans.size(); ++i) {
                int v = upper_bound(st.begin(), st.end(), ans[i]) - st.begin() - 1;
                int t = allt[v][(ans[i] - st[v]) % (int)allt[v].size()];
                mrans.push_back({v, t});
            }
            vector<pair<int, int>> rans;
            for (int i = 0; i < (int)mrans.size(); ++i) {
                auto [v, t] = mrans[i];
                if (!rans.empty() && rans.back().first == v) rans.pop_back();
                rans.push_back({v, t});
            }
            while (!rans.empty() && rans.back().first == rans[0].first) {
                rans.pop_back();
            }
            cout << "YES" << endl;
            cout << (int)rans.size() << " ";
            for (int i = 0; i < (int)rans.size(); ++i) {
                int j = (i + 1) % (int)rans.size();
                int u = edg[upper_bound(edg.begin(), edg.end(), array<int, 4>{rans[i].first, rans[j].first, rans[i].second, -1}) - edg.begin()][3];
                cout << u + 1 << " ";
            }
            cout << endl;
        }
    }
}
