#include<bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")

using namespace std;
using ull = unsigned long long;
const int MAX = 2e6 + 1, P = 1e9 + 7;

int pr[MAX];
int sz[MAX];
ull hs[MAX];
ull pows[MAX];

void update(int v, int in, int tp) {
    hs[v] += (ull)(tp) * pows[in];
}

int root(int v) {
    if (pr[v] == v) return v;
    return pr[v] = root(pr[v]);
}

int cnt = 0;
long long ans = 0;
map<ull, int> all;

void unite(int u, int v) {
    u = root(u);
    v = root(v);
    if (u == v) return;
    if (sz[u] < sz[v]) swap(u, v);
    if (hs[u] != 0) cnt--;
    if (hs[v] != 0) cnt--;
    if (hs[u] != 0) ans -= 1ll * 2 * all[hs[u]] * sz[u];
    if (hs[u] != 0) all[-hs[u]] -= sz[u];
    if (hs[v] != 0) ans -= 1ll * 2 * all[hs[v]] * sz[v];
    if (hs[v] != 0) all[-hs[v]] -= sz[v];
    pr[v] = u;
    sz[u] += sz[v];
    hs[u] += hs[v];
    if (hs[u] != 0) cnt++;
    if (hs[u] != 0) ans += 1ll * 2 * all[hs[u]] * sz[u];
    if (hs[u] != 0) all[-hs[u]] += sz[u];
}

void sw(int u, int v, vector<int> & p) {
    int x = p[u];
    int y = p[v];
    swap(p[u], p[v]);
    u = root(u);
    v = root(v);
    if (hs[u] != 0) cnt--;
    if (hs[v] != 0) cnt--;
    if (hs[u] != 0) ans -= 1ll * 2 * all[hs[u]] * sz[u];
    if (hs[u] != 0) all[-hs[u]] -= sz[u];
    if (hs[v] != 0) ans -= 1ll * 2 * all[hs[v]] * sz[v];
    if (hs[v] != 0) all[-hs[v]] -= sz[v];
    update(u, x, -1);
    update(u, y, 1);
    update(v, x, 1);
    update(v, y, -1);
    if (hs[u] != 0) cnt++;
    if (hs[u] != 0) ans += 1ll * 2 * all[hs[u]] * sz[u];
    if (hs[u] != 0) all[-hs[u]] += sz[u];
    if (hs[v] != 0) cnt++;
    if (hs[v] != 0) ans += 1ll * 2 * all[hs[v]] * sz[v];
    if (hs[v] != 0) all[-hs[v]] += sz[v];
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    pows[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        pows[i] = pows[i - 1] * P;
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        pr[i] = i;
        sz[i] = 1;
        hs[i] = 0;
    }
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        update(i, p[i], 1);
    }
    vector<int> q = p;
    sort(q.begin(), q.end());
    cnt = n;
    for (int i = 0; i < n; ++i) {
        update(i, q[i], -1);
        if (p[i] == q[i]) cnt--;
        if (hs[i] != 0) all[-hs[i]]++;
    }
    for (int i = 0; i < n; ++i) {
        if (hs[i] != 0) ans += all[hs[i]];
    }
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            sw(a, b, p);
        } else if (t == 2) {
            int a, b;
            cin >> a >> b;
            --a; --b;
            unite(a, b);
        } else if (t == 3) {
            if (cnt == 0) {
                cout << "DA" << '\n';
            } else {
                cout << "NE" << '\n';
            }
        } else {
            cout << ans / 2 << '\n';
        }
    }
    return 0;
}
