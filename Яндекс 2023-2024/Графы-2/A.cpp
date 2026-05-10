#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5 + 5;
vector<int> p(MAX);

int root(int v) {
    if (v == p[v]) {
        return v;
    }
    return p[v] = root(p[v]);
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        p[i] = i;
    }
    vector<array<int, 3>> g;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g.push_back({c, a, b});
    }
    sort(g.begin(), g.end());
    long long ans = 0;
    for (auto [w, v, to] : g) {
        if (root(v) != root(to)) {
            ans += w;
            p[root(to)] = v;
        }
    }
    cout << ans << endl;
    return 0;
}
