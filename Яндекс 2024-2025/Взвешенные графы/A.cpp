#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5;
int p[MAX], sz[MAX], now[MAX];
int ans = 0;

int root(int v) {
    ans += now[v];
    if (p[v] == v) {
        return v;
    }
    return root(p[v]);
}

void unite(int v, int u) {
    v = root(v);
    u = root(u);
    if (v == u) return;
    if (sz[v] < sz[u]) {
        swap(u, v);
    }
    p[u] = v;
    sz[v] += sz[u];
    now[u] -= now[v];
}

signed main() {
    ios_base::sync_with_stdio();
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        p[i] = i;
        sz[i] = 1;
        now[i] = 0;
    }
    for (int i = 0; i < m; ++i) {
        string t;
        cin >> t;
        if (t == "join") {
            int x, y;
            cin >> x >> y;
            --x; --y;
            unite(x, y);
        } else if (t == "add") {
            int x, c;
            cin >> x >> c;
            --x;
            now[root(x)] += c;
        } else {
            ans = 0;
            int x;
            cin >> x;
            --x;
            root(x);
            cout << ans << endl;
        }
    }
    return 0;
}
