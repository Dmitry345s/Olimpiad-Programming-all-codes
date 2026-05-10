#include<bits/stdc++.h>

using namespace std;

const int MAX = 200, INF = 1e9;

struct Ed {
    int v, c;
    Ed(int v = 0, int c = 0) : v(v), c(c) {};
};

vector<Ed> ed;
vector<int> g[MAX];

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

int dfs(int v, int fl, int k) {
    used[v] = 1;
    if (v == t) return fl;
    for (int in : g[v]) {
        auto [to, c] = ed[in];
        if (used[to] || c < (1 << k)) continue;
        int x = dfs(to, min(c, fl), k);
        if (x == 0) continue;
        upd(in, x);
        return x;
    }
    return 0;
}

int ch(vector<int> a, vector<vector<int>> all, int n, int m, int x) {
    for (int i = 0; i < MAX; ++i) {
        g[i].clear();
    }
    ed.clear();
    t = 1 + n + m;
    for (int i = 0; i < m; ++i) {
        add(i + n + 1, t, a[i]);
    }
    for (int i = 0; i < n; ++i) {
        add(0, i + 1, x);
        for (int u : all[i]) {
            add(i + 1, u + n, INF);
        }
    }
    int ans = 0;
    while (true) {
        fill(used, used + MAX, 0);
        int x = dfs(0, INF, 0);
        if (x == 0) break;
        ans += x;
    }
    return ans == x * n;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> all(n);
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        all[i].resize(c);
        for (int j = 0; j < c; ++j) {
            cin >> all[i][j];
        }
    }
    int l = 0, r = INF;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        if (ch(a, all, n, m, c)) {
            l = c;
        } else {
            r = c;
        }
    }
    cout << l << endl;
    return 0;
}
