#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 5, LN = 18;
vector<pair<int, int>> g[MAX];
int sz[MAX];
vector<int> used(MAX, -1);

void f_c(int v, int p, int t_sz, int & cent) {
    int mx = 0;
    sz[v] = 1;
    for (auto [to, len] : g[v]) {
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

int up[MAX][LN];
vector<vector<int>> cd(MAX, vector<int> (LN, -1));
vector<array<int, 3>> to_ans[MAX];

void dfs(int v, int p, int now, int num, int d) {
    cd[v][num] = now;
    up[v][num] = d;
    for (auto [to, len] : g[v]) {
        if (used[to] != -1 || to == p) continue;
        dfs(to, v, now, num, d + len);
    }
}

void solve(int v, int t_sz, int num) {
    int cent;
    f_c(v, -1, t_sz, cent);
    used[cent] = num;
    dfs(cent, cent, cent, num, 0);
    for (auto [to, len] : g[cent]) {
        if (used[to] == -1) {
            int sz_to = sz[to];
            if (sz[to] > sz[cent]) {
                sz_to = t_sz - sz[cent];
            }
            solve(to, sz_to, num + 1);
        }
    }
}

void add(int v, int k, int x, int time) {
    for (int i = 0; i < LN; ++i) {
        if (cd[v][i] == -1) break;
        int k2 = k - up[v][i];
        if (k2 < 0) continue;
        while ((int)to_ans[cd[v][i]].size() > 0 && to_ans[cd[v][i]].back()[0] <= k2) {
            to_ans[cd[v][i]].pop_back();
        }
        to_ans[cd[v][i]].push_back({k2, x, time});
    }
}

int get(int v) {
    int now = -1;
    int ans = 0;
    for (int i = 0; i < LN; ++i) {
        if (cd[v][i] == -1) continue;
        int k = up[v][i];
        //cout << k << endl;
        //reverse(to_ans[cd[v][i]].begin(), to_ans[cd[v][i]].end());
        auto it = lower_bound(to_ans[cd[v][i]].rbegin(), to_ans[cd[v][i]].rend(), array<int, 3>{k, -1, -1});
        if (it == to_ans[cd[v][i]].rend()) continue;
        if ((*it)[2] > now) {
            now = (*it)[2];
            ans = (*it)[1];
        }
        //reverse(to_ans[cd[v][i]].begin(), to_ans[cd[v][i]].end());
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, w;
        cin >> a >> b >> w;
        --a; --b;
        g[a].push_back({b, w});
        g[b].push_back({a, w});
    }
    solve(0, n, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int v, d, c;
            cin >> v >> d >> c;
            --v;
            add(v, d, c, i);
        } else {
            int v;
            cin >> v;
            --v;
            cout << get(v) << endl;
        }
    }
    return 0;
}
/*5
1 2 30
1 3 50
3 4 70
3 5 60
8
1 3 72 6
2 5
1 4 60 5
2 3
2 2
1 2 144 7
2 4*/
