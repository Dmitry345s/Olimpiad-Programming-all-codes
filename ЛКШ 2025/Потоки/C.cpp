#include<bits/stdc++.h>

using namespace std;

const int MAX = 300, INF = 1e9;

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
    int sum = 0;
    for (int i = 1; i <= n; ++i) {
        int v;
        cin >> v;
        if (v > 0) {
            sum += v;
            add(0, i, v);
        } else {
            add(i, n + 1, -v);
        }
    }
    for (int i = 1; i <= n; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int v;
            cin >> v;
            add(i, v, INF);
        }
    }
    t = n + 1;
    int ans = sum;
    while (true) {
        fill(used, used + n + 2, 0);
        int fl = dfs(0, INF, 0);
        ans -= fl;
        if (fl == 0) break;
    }
    cout << ans << endl;
    return 0;
}
