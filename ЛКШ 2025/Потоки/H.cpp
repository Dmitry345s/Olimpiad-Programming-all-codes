#include<bits/stdc++.h>

using namespace std;

const int MAX = 500, INF = 1e9, LN = 29;

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
        int x = dfs(to, min(fl, c), k);
        if (x == 0) continue;
        upd(in, x);
        return x;
    }
    return 0;
}

signed main() {
    int n;
    cin >> n;
    vector<int> now(n);
    for (int i = 0; i < n; ++i) {
        cin >> now[i];
    }
    for (int i = 0; i < n; ++i) {
        int v;
        cin >> v;
        if (i == 0) {
            now[i] += v;
        }
    }
    vector<vector<int>> g(n, vector<int> (n));
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> g[i][j];
            if (i == 0 || j == 0 || i > j) {
                g[i][j] = 0;
            }
            add(0, i * n + j + 1, g[i][j]);
            add(i * n + j + 1, n * n + 1 + i, g[i][j]);
            add(i * n + j + 1, n * n + 1 + j, g[i][j]);
            sum += g[i][j];
        }
    }
    t = n * n + n + 1;
    for (int i = 0; i < n; ++i) {
        if (now[i] > now[0]) {
            cout << "NO" << endl;
            return 0;
        }
        add(n * n + 1 + i, t, now[0] - now[i]);
    }
    int ans = 0;
    for (int i = LN - 1; i >= 0; --i) {
        while (true) {
            fill(used, used + MAX, 0);
            int x = dfs(0, INF, i);
            if (x == 0) break;
            ans += x;
        }
    }
    if (ans == sum) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
