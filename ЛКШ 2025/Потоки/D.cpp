#include<bits/stdc++.h>

using namespace std;
using ld = long double;
using ll = long long;

const ll MAX = 1004, INF = 2e12, INF2 = 1e9;

struct Ed {
    int v, c;
    Ed(int v = 0, int c = 0) : v(v), c(c) {}
};

vector<int> g[MAX];
vector<Ed> ed;

void add(int v, int u, int c) {
    g[v].push_back((int)ed.size());
    ed.push_back(Ed(u, c));
    g[u].push_back((int)ed.size());
    ed.push_back(Ed(v, 0));
}

void upd(int in, int x) {
    ed[in].c -= x;
    ed[(in ^ 1)].c += x;
}

int t;
int used[MAX];
int ind[MAX];
int d[MAX];

void bfs() {
    queue<int> q;
    fill(d, d + t + 1, INF2);
    d[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int in : g[v]) {
            auto [to, c] = ed[in];
            if (c == 0 || d[v] + 1 >= d[to]) continue;
            d[to] = d[v] + 1;
            q.push(to);
        }
    }
}

int dfs(int v, int fl) {
    used[v] = 1;
    if (v == t) return fl;
    for (int i = ind[v]; i < (int)g[v].size(); ++i) {
        int in = g[v][i];
        auto [to, c] = ed[in];
        ind[v] = i;
        if (used[to] || c < 1 || d[v] + 1 != d[to]) continue;
        int x = dfs(to, min(fl, c));
        if (x == 0) continue;
        upd(in, x);
        return x;
    }
    return 0;
}

ll get_d(int x1, int y1, int x2, int y2) {
    ll xd = 1ll * (x1 - x2) * (x1 - x2);
    ll yd = 1ll * (y1 - y2) * (y1 - y2);
    return xd + yd;
}

int ch(ll dist, vector<pair<int, int>> u, vector<array<int, 3>> u2) {
    for (int i = 0; i < MAX; ++i) {
        g[i].clear();
    }
    ed.clear();
    t = 1 + (int)u.size() + (int)u2.size();
    for (int i = 1; i <= (int)u.size(); ++i) {
        add(0, i, 1);
    }
    for (int i = (int)u.size() + 1; i < t; ++i) {
        add(i, t, u2[i - (int)u.size() - 1][2]);
    }
    for (int i = 0; i < (int)u.size(); ++i) {
        for (int j = 0; j < (int)u2.size(); ++j) {
            ll ds = get_d(u[i].first, u[i].second, u2[j][0], u2[j][1]);
            if (ds <= dist) {
                add(i + 1, j + 1 + (int)u.size(), 1);
            }
        }
    }
    int ans = 0;
    while (true) {
        bfs();
        if (d[t] == INF2) break;
        fill(ind, ind + t + 1, 0);
        while (true) {
            fill(used, used + t + 1, 0);
            int x = dfs(0, 1);
            ans += x;
            if (x == 0) break;
        }
        //cout << ans << endl;
    }
    return ans == (int)u.size();
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> u(n);
    vector<array<int, 3>> u2(m);
    for (int i = 0; i < n; ++i) {
        cin >> u[i].first >> u[i].second;
    }
    for (int i = 0; i < m; ++i) {
        cin >> u2[i][0] >> u2[i][1] >> u2[i][2];
    }
    ll l = 0, r = INF;
    while (l + 1 < r) {
        ll c = (l + r) / 2;
        if (ch(c, u, u2)) {
            r = c;
        } else {
            l = c;
        }
    }
    cout << setprecision(20) << sqrtl(r) << endl;
    return 0;
}
