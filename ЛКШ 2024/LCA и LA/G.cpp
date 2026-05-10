#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 5, LN = 20;
vector<vector<int>> g(MAX), up(MAX, vector<int> (LN));
vector<int> tin(MAX), tout(MAX), used(MAX), h(MAX);
int timer = 0;

void dfs(int v, int p, int num) {
    used[v] = num;
    h[v] = h[p] + 1;
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v, num);
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    for (int i = LN - 1; i >= 0; --i) {
        if (!(up[a][i] >= b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> c(k + 1);
    for (int i = 0; i < m; ++i) {
        int s, t, a;
        cin >> s >> t >> a;
        --s; --t;
        c[a].push_back({s, t});
    }
    for (int i = 0; i <= k; ++i) {
        sort(c[i].begin(), c[i].end());
    }
    vector<pair<int, int>> all;
    for (int i = 1; i <= k; ++i) {
        int last = 0;
        for (int j = 0; j < (int)c[i].size(); ++j) {
            if (last != c[i][j].first) {
                //cout << i << " " << last << " " << c[i][j].first << endl;
                all.push_back({last, c[i][j].first});
            }
            last = c[i][j].second;
        }
        if (last != n - 1) {
            //cout << i << " " << last << " " << n - 1 << endl;
            all.push_back({last, n - 1});
        }
    }
    //cout << 1 << endl;
    vector<vector<int>> scan(n + 1);
    for (int i = 0; i < (int)all.size(); ++i) {
        //cout << all[i].first << " " << all[i].second << endl;
        scan[all[i].first].push_back(-(i + 1));
        scan[all[i].second + 1].push_back(i + 1);
    }
    //cout << 1 << endl;
    set<pair<int, int>> st;
    vector<int> to(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (int)scan[i].size(); ++j) {
            if (scan[i][j] < 0) {
                int now = -scan[i][j] - 1;
                st.insert({-all[now].second, now});
            } else {
                int now = scan[i][j] - 1;
                st.erase({-all[now].second, now});
            }
        }
        to[i] = i;
        if (!st.empty()) {
            to[i] = max(-(*st.begin()).first, to[i]);
        }
    }
    //cout << 1 << endl;
    for (int i = 0; i < n; ++i) {
        g[to[i]].push_back(i);
        //cout << to[i] << " " << i << endl;
    }
    int num = 1;
    for (int i = n - 1; i >= 0; --i) {
        if (used[i] == 0) {
            dfs(i, i, num);
            num++;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l; --r;
        if (used[l] != used[r]) {
            cout << -1 << endl;
        } else {
            int cnt = 0;
            int cnt2 = h[l] - h[lca(l, r)];
            cout << cnt2 << endl;
            //assert(cnt2 == cnt);
        }
    }
    return 0;
}
