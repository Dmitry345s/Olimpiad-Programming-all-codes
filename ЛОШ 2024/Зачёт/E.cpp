#include<bits/stdc++.h>

//#define int long long

using namespace std;

int MAX = 2e5 + 5;
vector<vector<pair<int, int>>> g(MAX);
vector<int> ch, used, hs;
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
vector<int> sz(MAX);

pair<int, int> root(int v) {
    if (p[v] == v) {
        return {v, 0};
    }
    pair<int, int> k = root(p[v]);
    now[v] ^= k.second;
    p[v] = k.first;
    return {p[v], now[v]};
}

void unite(int a, int b, int ch) {
    if (sz[a] < sz[b]) {
        swap(a, b);
    }
    p[b] = a;
    sz[a] += sz[b];
    now[b] ^= ch;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
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
    g.clear();
    vector<pair<int, int>> qs(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i].first >> qs[i].second;
        qs[i].first--;
    }
    vector<int> anses(m + 1);
    vector<int> qs2(q);
    for (int _ = 0; _ < min(200, m); ++_) {
        for (int i = 0; i < n; ++i) {
            p[i] = i;
            now[i] = 0;
            sz[i] = 1;
        }
        int flag = 0;
        for (int i = 0; i < _; ++i) {
            auto[v1, v2] = my[i];
            pair<int, int> rv1 = root(v1), rv2 = root(v2);
            if (rv1.first == rv2.first) {
                if ((now[v1] ^ now[rv1.first]) == (now[v2] ^ now[rv2.first])) {
                    flag = 1;
                }
            } else {
                unite(rv1.first, rv2.first, (now[v1] ^ now[v2] ^ 1 ^ now[rv1.first] ^ now[rv2.first]));
            }
        }
        //cout << _ << " " << flag << endl;
        anses[m] = flag;
        for (int i = m - 1; i >= _; --i) {
            //cout << _ << " " << flag << endl;
            auto[v1, v2] = my[i];
            pair<int, int> rv1 = root(v1), rv2 = root(v2);
            if (rv1.first == rv2.first) {
                if ((now[v1] ^ now[rv1.first]) == (now[v2] ^ now[rv2.first])) {
                    flag = 1;
                }
            } else {
                unite(rv1.first, rv2.first, (now[v1] ^ now[v2] ^ 1 ^ now[rv1.first] ^ now[rv2.first]));
            }
            anses[i] = flag;
        }
        for (int i = 0; i < q; ++i) {
            if (qs[i].first == _) {
                qs2[i] = anses[qs[i].second];
            }
        }
    }
    for (int i = 0; i < q; ++i) {
        if (qs2[i]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
