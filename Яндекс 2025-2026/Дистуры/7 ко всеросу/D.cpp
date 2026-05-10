#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

#define int long long

using namespace std;

const int MAX = 2e3 + 1, INF = 1e18;
vector<int> g[MAX];
array<int, 3> all[2 * MAX];
vector<pair<int, int>> gr[MAX];

void upd(vector<pair<int, int>> & tree, pair<int, int> a, int v, int n) {
    v += n;
    tree[v] = a;
    v /= 2;
    while (v >= 1) {
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
        v /= 2;
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, t, k;
    cin >> n >> m >> t >> k;
    vector<vector<int>> ch(n, vector<int> (n));
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        gr[a].push_back({b, c});
        gr[b].push_back({a, c});
        g[a].push_back(2 * i);
        g[b].push_back(2 * i + 1);
        all[2 * i] = {a, b, c};
        all[2 * i + 1] = {b, a, c};
        ch[a][b] = 1;
        ch[b][a] = 1;
    }
    vector<int> x(k);
    for (int i = 0; i < k; ++i) {
        cin >> x[i];
        --x[i];
    }
    for (int _ = 0; _ < t; ++_) {
        int p, q;
        cin >> p >> q;
        --p; --q;
        x[p] = q;
        vector<int> d(n, INF);
        vector<int> wg(n, INF);
        for (auto [to, c] : gr[x[0]]) {
            d[to] = -c;
        }
        for (int i = 0; i < k - 1; ++i) {
            vector<pair<int, int>> tree(2 * n);
            for (int j = n; j < 2 * n; ++j) {
                tree[j] = {INF, j - n};
            }
            for (int j = n - 1; j >= 1; --j) {
                tree[j] = min(tree[2 * j], tree[2 * j + 1]);
            }
            int mn1 = INF, mn2 = INF;
            for (auto [to, c] : gr[x[i]]) {
                int rd = d[to] + c;
                if (i > 0 && to == x[i - 1]) rd = wg[x[i]];
                if (rd <= mn1) {
                    mn2 = mn1;
                    mn1 = rd;
                } else if (rd < mn2) {
                    mn2 = rd;
                }
            }
            if (i == 0) {
                mn1 = 0;
                mn2 = 0;
            }
            vector<int> nd(n, INF);
            for (auto [to, c] : gr[x[i]]) {
                int rd = d[to] + c;
                if (i > 0 && to == x[i - 1]) rd = wg[x[i]];
                /*if (i > 0 && x[i - 1] == x[i + 1] && to == x[i + 1]) {
                    if (rd == mn1) {
                        nd[to] = min(nd[to], mn2 + c);
                        upd(tree, {nd[to], to}, to, n);
                    } else {
                        nd[to] = min(nd[to], mn1 + c);
                        upd(tree, {nd[to], to}, to, n);
                    }
                    nd[to] = INF;
                    continue;
                }*/
                if (rd == mn1) {
                    nd[to] = min(nd[to], mn2 + c);
                    upd(tree, {nd[to], to}, to, n);
                } else {
                    nd[to] = min(nd[to], mn1 + c);
                    upd(tree, {nd[to], to}, to, n);
                }
            }
            wg = nd;
            /*cout << mn1 << " " << mn2 << endl;
            for (int i = 0; i < n; ++i) {
                cout << nd[i] << " ";
            }
            cout << endl;*/
            while (true) {
                auto [nds, v] = tree[1];
                //cout << nds << " " << v << endl;
                if (nds == INF) break;
                upd(tree, {INF, v}, v, n);
                for (auto [to, c] : gr[v]) {
                    //cout << nd[to] << " " << nds << " " << v << endl;
                    if (nd[to] > nds + c) {
                        nd[to] = nds + c;
                        upd(tree, {nd[to], to}, to, n);
                        if (v == x[i + 1]) {
                            nd[to] = INF;
                        }
                    }
                }
            }
            nd[x[i]] = INF;
            /*for (int i = 0; i < n; ++i) {
                cout << nd[i] << " ";
            }
            cout << endl;*/
            //nd[x[i]] = INF;
            //cout << nd[x[i]] << endl;
            swap(nd, d);
        }
        int ans = INF;
        for (auto [to, c] : gr[x[k - 1]]) {
            int rd = d[to] + c;
            if (k - 1 > 0 && to == x[k - 2]) rd = wg[x[k - 1]];
            ans = min(ans, rd);
        }
        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
    }
    return 0;
}
/*
4 4 1 3
1 2 1
2 3 1
1 3 1
1 4 1
4
1
3
3 4
*/
/*
if (to == x[i + 1]) {
    if (rd == mn1) {
        nd[to] = min(nd[to], mn2 + c);
        upd(tree, {nd[to], to}, to, n);
    } else {
        nd[to] = min(nd[to], mn1 + c);
        upd(tree, {nd[to], to}, to, n);
    }
    nd[to] = INF;
    continue;
}
*/
