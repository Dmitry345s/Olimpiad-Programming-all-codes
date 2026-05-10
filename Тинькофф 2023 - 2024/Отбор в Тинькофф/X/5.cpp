#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")

using namespace std;

const int MAX = 1e5, ln = 17;
vector<vector<int>> g(MAX);
int up[ln][MAX];
int tin[MAX], tout[MAX], tin2[MAX];
vector<int> ord;
map<pair<int, int>, int> mp;
int timer = 0;

void dfs(int v, int p) {
    tin[v] = timer++;
    up[0][v] = p;
    for (int i = 1; i < ln; ++i) {
        up[i][v] = up[i - 1][up[i - 1][v]];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        int j = mp[{min(v, to), max(v, to)}];
        tin2[j] = ord.size();
        ord.push_back(j);
        dfs(to, v);
        ord.push_back(j);
    }
    tout[v] = timer++;
}

bool check(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    for (int i = ln - 1; i >= 0; --i) {
        if (!check(up[i][a], b)) {
            a = up[i][a];
        }
    }
    return a;
}

int get(int s, int t) {
    if (check(s, t)) {
        return lca(t, s);
    } else {
        return up[0][s];
    }
}

int k = 800;
int tree[4 * (MAX + 1)];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v + 1, l, m);
    build(2 * v + 2, m, r);
    tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v + 1, l, m, id, x);
    } else {
        update(2 * v + 2, m, r, id, x);
    }
    tree[v] = min(tree[2 * v + 1], tree[2 * v + 2]);
}

int get(int v, int l, int r) {
    if (l + 1 == r) {
        return l;
    }
    int m = (l + r) / 2;
    if (tree[2 * v + 1] == 0) {
        return get(2 * v + 1, l, m);
    }
    return get(2 * v + 2, m, r);
}

signed main() {
    ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> cs(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
        if (c > n) {
            c = n;
        }
        cs[i] = c;
        mp[{min(a, b), max(a, b)}] = i;
    }
    dfs(0, 0);
    /*for (int i = 0; i < 2 * (n - 1); ++i) {
        cout << ord[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < 2 * (n - 1); ++i) {
        cout << cs[ord[i]] << " ";
    }
    cout << endl << endl;*/
    vector<array<int, 3>> qs;
    vector<int> ans(q);
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (a == b) {
            ans[i] = 0;
            continue;
        }
        int geta = get(a, b), getb = get(b, a);
        pair<int, int> f = {min(a, geta), max(a, geta)}, s = {min(b, getb), max(b, getb)};
        int t1 = tin2[mp[f]], t2 = tin2[mp[s]];
        qs.push_back({min(t1, t2), max(t1, t2), i});
        //cout << t1 << " " << t2 << endl;
    }
    sort(qs.begin(), qs.end());
    vector<vector<array<int, 3>>> qs2(((int)ord.size() + k - 1) / k);
    for (int i = 0; i < (int)qs.size(); ++i) {
        auto [l, r, j] = qs[i];
        qs2[l / k].push_back({r, l, j});
    }
    //cout << qs.size() << endl;
    vector<int> rnums(n - 1);
    for (int i = 0; i < (int)qs2.size(); ++i) {
        sort(qs2[i].begin(), qs2[i].end());
        build(0, 0, n + 1);
        vector<int> nums = rnums;
        int l = k * i, r = k * i - 1;
        for (int j = 0; j < (int)qs2[i].size(); ++j) {
            auto [qr, ql, u] = qs2[i][j];
            //cout << ql << " " << qr << " " << u << endl;
            for (int i2 = r + 1; i2 <= qr; ++i2) {
                int j2 = ord[i2];
                nums[j2] += 1;
                if (nums[j2] % 2 == 0) {
                    update(0, 0, n + 1, cs[j2], -1);
                } else {
                    update(0, 0, n + 1, cs[j2], 1);
                }
            }
            for (int i2 = l; i2 < ql; ++i2) {
                int j2 = ord[i2];
                nums[j2] -= 1;
                if (nums[j2] % 2 == 0) {
                    update(0, 0, n + 1, cs[j2], -1);
                } else {
                    update(0, 0, n + 1, cs[j2], 1);
                }
            }
            for (int i2 = l - 1; i2 >= ql; --i2) {
                int j2 = ord[i2];
                nums[j2] += 1;
                if (nums[j2] % 2 == 0) {
                    update(0, 0, n + 1, cs[j2], -1);
                } else {
                    update(0, 0, n + 1, cs[j2], 1);
                }
            }
            int j2 = ord[ql];
            if (nums[j2] % 2 == 0) {
                nums[j2] -= 1;
                update(0, 0, n + 1, cs[j2], 1);
                ++ql;
            }
            l = ql;
            r = qr;
            ans[u] = get(0, 0, n + 1);
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}
