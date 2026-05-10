#include<bits/stdc++.h>

using namespace std;

int mod = 1e6 + 3, MAX = 2e5;
vector<int> p(MAX), sm(MAX, 0), mn(MAX, 0), sz(MAX);
int zerg = 0;

int root(int v) {
    if (v == p[v]) {
        return v;
    }
    return root(p[v]);
}

void unite(int v, int u) {
    v = root(v);
    u = root(u);
    if (u == v) {
        return;
    }
    if (sz[v] < sz[u]) {
        swap(u, v);
    }
    p[u] = v;
    sz[v] += sz[u];
    sm[u] -= sm[v];
}

int get(int v, int ans) {
    ans += sm[v];
    if (v == p[v]) {
        return ans;
    }
    return get(p[v], ans);
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        sz[i] = 1;
    }
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            x = (x + zerg) % n;
            sm[root(x)] += 1;
            zerg = (30 * zerg + 239) % mod;
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            x = (x + zerg) % n;
            y = (y + zerg) % n;
            if (root(x) == root(y)) continue;
            unite(x, y);
            zerg = (13 * zerg + 11) % mod;
        } else {
            int x;
            cin >> x;
            x = (x + zerg) % n;
            int ans = get(x, mn[x]);
            cout << ans << endl;
            mn[x] -= ans;
            zerg = (1ll * 100500 * zerg + ans) % mod;
        }
    }
    return 0;
}
