#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 2;
pair<int, int> all[MAX];
int qs[MAX];
vector<int> tree[4 * MAX];

void update(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        tree[v].push_back(x);
        return;
    }
    int m = (l + r) / 2;
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
}

int cl[MAX];
vector<int> g[MAX];

void dfs(int v, int p, int now) {
    cl[v] = now;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v, (now ^ 1));
    }
}

int p[MAX];
int sz[MAX][2];

int root(int v) {
    if (p[v] == v) {
        return v;
    }
    return root(p[v]);
}

vector<pair<int, int>> ot;

void unite(int v, int u) {
    int rv = root(v), ru = root(u);
    if (rv == ru) {
        ot.push_back({-1, -1});
        return;
    }
    if (sz[rv][0] + sz[rv][1] < sz[ru][0]+ sz[ru][1]) {
        swap(rv, ru);
    }
    p[ru] = rv;
    ot.push_back({rv, ru});
    sz[rv][0] += sz[ru][0];
    sz[rv][1] += sz[ru][1];
}

void del() {
    auto [rv, ru] = ot.back();
    ot.pop_back();
    if (rv == -1 && ru == -1) return;
    sz[rv][0] -= sz[ru][0];
    sz[rv][1] -= sz[ru][1];
    p[ru] = ru;
}

vector<int> ans;

void get(int v, int l, int r) {
    //cout << l << " " << r << endl;
    for (int i = 0; i < (int)tree[v].size(); ++i) {
        unite(all[tree[v][i]].first, all[tree[v][i]].second);
    }
    if (l + 1 == r) {
        if (qs[l] != -1) {
            int rt = root(qs[l]);
            ans.push_back(min(sz[rt][0], sz[rt][1]));
        }
        for (int i = 0; i < (int)tree[v].size(); ++i) {
            del();
        }
        return;
    }
    int m = (l + r) / 2;
    get(2 * v, l, m);
    get(2 * v + 1, m, r);
    for (int i = 0; i < (int)tree[v].size(); ++i) {
        del();
    }
}

const int MAX2 = 200, INF = 1e9 + 7;
int h[MAX];
int used[MAX];
vector<pair<int, int>> g2[MAX];

void dfs1(int v, int p) {
    h[v] = INF;
    for (auto [to, in] : g2[v]) {
        if (!used[in] && to != p) {
            dfs1(to, v);
            h[v] = max(h[v], h[to] + 1);
        }
    }
    if (h[v] == INF) h[v] = 0;
}

bool cmp(pair<int, int> a, pair<int, int> b) {
    if (h[a.first] % 2 == h[b.first] % 2) {
        if (h[a.first] == h[b.first]) {
            return a < b;
        }
        return h[a.first] < h[b.first];
    }
    return h[a.first] % 2 < h[b.first] % 2;
}

vector<vector<int>> als;

void dfs2(int v, int p) {
    als.back().push_back(v);
    int cnt = 0;
    for (auto [to, in] : g2[v]) {
        if (!used[in] && to != p) {
            if (cnt != 0) als.push_back({});
            dfs2(to, v);
            cnt++;
        }
    }
}

signed main() {
    int _;
    cin >> _;
    int n;
    cin >> n;
    vector<int> now(n - 1, -1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        all[i] = {a, b};
        g[a].push_back(b);
        g[b].push_back(a);
        g2[a].push_back({b, i});
        g2[b].push_back({a, i});
        now[i] = 0;
    }
    if (_ <= 1) {
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int t;
            cin >> t;
            if (t == 1) {
                int e;
                cin >> e;
                --e;
                used[e] ^= 1;
            } else {
                int x;
                cin >> x;
                --x;
                fill(h, h + n, INF);
                dfs1(x, x);
                for (int i = 0; i < n; ++i) {
                    sort(g2[i].begin(), g2[i].end(), cmp);
                }
                als.clear();
                als.push_back({});
                dfs2(x, x);
                int ans = 0;
                for (auto u : als) {
                    ans += (int)u.size() / 2;
                }
                cout << ans << '\n';
            }
        }
        return 0;
    }
    dfs(0, -1, 0);
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        sz[i][cl[i]] = 1;
    }
    int q;
    cin >> q;
    fill(qs, qs + q + 1, -1);
    for (int i = 0; i < q; ++i) {
        int t, x;
        cin >> t >> x;
        --x;
        if (t == 1) {
            if (now[x] == -1) {
                now[x] = i + 1;
            } else {
                update(1, 0, q + 1, now[x], i + 1, x);
                now[x] = -1;
            }
        } else {
            qs[i + 1] = x;
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        if (now[i] != -1) {
            update(1, 0, q + 1, now[i], q + 1, i);
        }
    }
    get(1, 0, q + 1);
    for (int x : ans) {
        cout << x << endl;
    }
    return 0;
}
