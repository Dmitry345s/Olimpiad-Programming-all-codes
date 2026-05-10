#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5;
vector<int> g[MAX];
int sz[MAX];
int used[MAX];
int d, n;

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

vector<pair<int, int>> all;
vector<int> all2;
int ans[MAX];
int tree[MAX];

void update1(int in, int x) {
    for (int i = in; i < n; i = (i | (i + 1))) {
        tree[i] += x;
    }
}

int get(int in) {
    int ans = 0;
    for (int i = in; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

void dfs(int v, int p, int last) {
    update1(last, 1);
    for (int to : g[v]) {
        if (to == p || used[to] != -1) continue;
        dfs(to, v, last + 1);
    }
}

void dfs2(int v, int p, int now, int last) {
    all2.push_back(last);
    if (v != now) {
        all.push_back({v, last});
    } else {
        ans[v] += get(d);
        //cout << v << " " << ans[v] << endl;
    }
    for (int to : g[v]) {
        if (to == p || used[to] != -1) continue;
        dfs2(to, v, now, last + 1);
        if (v == now) {
            for (int i = 0; i < (int)all.size(); ++i) {
                //cout << to << " " << all[i].first << " " << all[i].second << endl;
                update1(all[i].second, -1);
            }
            for (int i = 0; i < (int)all.size(); ++i) {
                ans[all[i].first] += get(d - all[i].second);
            }
            for (int i = 0; i < (int)all.size(); ++i) {
                update1(all[i].second, 1);
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
    dfs2(cent, cent, cent, 0);
    //cout << cent << endl;
    for (int i = 0; i < (int)all2.size(); ++i) {
        update1(all2[i], -1);
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
    cin >> n >> d;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    all.reserve(n + 1);
    all2.reserve(n + 1);
    for (int i = 0; i < n; ++i) {
        used[i] = -1;
        tree[i] = 0;
    }
    solve(0, 0, n);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
