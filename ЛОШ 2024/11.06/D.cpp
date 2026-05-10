#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 2e5 + 5;
vector<vector<pair<int, int>>> g(MAX);
vector<int> ch(MAX), used(MAX), hs(MAX);
int flag = 0;

void dfs(int v, int p = 0) {
    used[v] = 1;
    hs[v] = hs[p] + 1;
    //cout << v << " " << p << " " << hs[v] << endl;
    for (auto [to, i] : g[v]) {
        if (ch[i] == 1) continue;
        //cout << v << " " << to << endl;
        if (used[to]) {
            //cout << "? " << to << endl;
            if (abs(hs[v] - hs[to]) % 2 == 0) {
                flag = 1;
            }
            continue;
        }
        dfs(to, v);
    }
}

vector<int> p(MAX), now(MAX);
vector<vector<int>> all(MAX);

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return root(p[v]);
}

void unite(int a, int b) {
    if (all[a].size() < all[b].size()) {
        p[a] = b;
        if (now[a] == now[b]) {
            for (int i = 0; i < (int)all[a].size(); ++i) {
                now[all[a][i]] = (now[all[a][i]] + 1) % 2;
            }
        }
        for (int i = 0; i < (int)all[a].size(); ++i) {
            all[b].push_back(all[a][i]);
        }
        all[a].clear();
    } else {
        p[b] = a;
        if (now[a] == now[b]) {
            for (int i = 0; i < (int)all[b].size(); ++i) {
                now[all[b][i]] = (now[all[b][i]] + 1) % 2;
            }
        }
        for (int i = 0; i < (int)all[b].size(); ++i) {
            all[a].push_back(all[b][i]);
        }
        all[b].clear();
    }
}

signed main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<pair<int, int>> my(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back({b, i});
        g[b].push_back({a, i});
        my[i] = {a, b};
    }
    if (n <= 2000 && m <= 2000 && q <= 2000) {
        for (int i = 0; i < q; ++i) {
            used.assign(n, 0);
            ch.assign(m, 0);
            hs.assign(n, 0);
            int l, r;
            cin >> l >> r;
            --l;
            for (int j = l; j < r; ++j) {
                ch[j] = 1;
            }
            flag = 0;
            for (int i = 0; i < n; ++i) {
                if (!used[i]) {
                    dfs(i, i);
                }
            }
            if (flag == 1) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        now[i] = 0;
        all[i] = {i};
    }
    vector<int> to_ans(m + 1);
    int ans = 0;
    for (int i = m - 1; i >= 0; --i) {
        int r1 = root(my[i].first), r2 = root(my[i].second);
        if (r1 != r2) {
            unite(r1, r2);
        } else {
            if (now[my[i].first] == now[my[i].second]) {
                ans = 1;
            }
        }
        to_ans[i] = ans;
    }
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        if (to_ans[r]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
