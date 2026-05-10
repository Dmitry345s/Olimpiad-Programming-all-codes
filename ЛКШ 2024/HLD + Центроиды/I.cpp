#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5, INF = 1e9;
vector<int> g[MAX];
int sz[MAX];
int used[MAX];
int tree[4 * MAX];
int lst[MAX];
int n;
int mx = 0;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = INF;
        lst[l] = v;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
}

void update(int in, int x) {
    int v = lst[in];
    tree[v] = x;
    while (v != 1) {
        v /= 2;
        tree[v] = min(tree[2 * v], tree[2 * v + 1]);
    }
}

int get(int ql, int qr) {
    int v1 = lst[ql], v2 = lst[qr];
    int l_res = INF, r_res = INF;
    while (v1 < v2) {
        //cout << v1 << " " << v2 << " " << l_res << " " << r_res << endl;
        if (v1 % 2 == 1) {
            l_res = min(l_res, tree[v1]);
        }
        v1 = (v1 + 1) / 2;
        if (v2 % 2 == 0) {
            r_res = min(r_res, tree[v2]);
        }
        v2 = (v2 - 1) / 2;
    }
    if (v1 == v2) {
        l_res = min(l_res, tree[v1]);
    }
    return min(r_res, l_res);
}

void f_c(int v, int p, int t_sz, int & cent) {
    sz[v] = 1;
    int mx = 0;
    for (int to : g[v]) {
        if (to == p || used[to] != -1) continue;
        f_c(to, v, t_sz, cent);
        sz[v] += sz[to];
        mx = max(mx, sz[to]);
    }
    mx = max(mx, t_sz - sz[v]);
    if (mx <= t_sz / 2) {
        cent = v;
    }
}

void dfs(int v, int p, int last) {
    update(v, last);
    for (int to : g[v]) {
        if (to == p || used[to] != -1) continue;
        dfs(to, v, last + 1);
    }
}

vector<pair<int, int>> all;
vector<int> all2;
vector<int> ans(MAX, INF);

void dfs2(int v, int p, int last, int now) {
    if (now != v) {
        all.push_back({v, last});
    } else {
        update(v, last);
        ans[v] = min(ans[v], get(v + 1, n - 1));
        //cout << v << " " << ans[v] << endl;
    }
    all2.push_back(v);
    for (int to : g[v]) {
        if (to == p || used[to] != -1) continue;
        dfs2(to, v, last + 1, now);
        if (v == now) {
            for (int i = 0; i < (int)all.size(); ++i) {
                //cout << to << " " << all[i].first << " " << all[i].second << endl;
                update(all[i].first, INF);
            }
            for (int i = 0; i < (int)all.size(); ++i) {
                ans[all[i].first] = min(ans[all[i].first], get(all[i].first + 1, n - 1) + all[i].second);
            }
            for (int i = 0; i < (int)all.size(); ++i) {
                update(all[i].first, all[i].second);
            }
            all.clear();
        }
    }
}

void solve(int v, int num, int t_sz) {
    int cent;
    f_c(v, -1, t_sz, cent);
    used[cent] = num;
    dfs(cent, cent, 0);
    dfs2(cent, cent, 0, cent);
    for (auto v : all2) {
        update(v, INF);
    }
    all2.clear();
    for (int to : g[cent]) {
        if (used[to] == -1) {
            int sz_to = sz[to];
            if (sz_to > sz[cent]) {
                sz_to = t_sz - sz[cent];
            }
            solve(to, num + 1, sz_to);
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    while (true) {
        if ((1 << mx) < n) {
            mx++;
        } else {
            break;
        }
    }
    build(1, 0, (1 << mx));
    for (int i = 0; i < n; ++i) {
        used[i] = -1;
    }
    solve(0, 0, n);
    for (int i = 0; i < n - 1; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
