#include<bits/stdc++.h>
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("O3")

#define int long long

using namespace std;

int MAX = 3e5;
vector<vector<pair<int, int>>> g(MAX);
vector<int> ps(MAX), ps2(MAX);

void dfs(int v, int p = -1, int p2 = -1) {
    ps[v] = p;
    ps2[v] = p2;
    for (auto[to, i] : g[v]) {
        if (to == p) continue;
        dfs(to, v, i);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> w(m);
    vector<pair<int, int>> all(m);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b >> w[i];
        --a; --b;
        all[i] = {a, b};
        g[a].push_back({b, i});
        g[b].push_back({a, i});
    }
    vector<int> mw(m);
    int maxm = w.back();
    mw.back() = maxm;
    for (int i = m - 2; i >= 0; --i) {
        mw[i] = w[i] + maxm;
        maxm = max(maxm, w[i]);
    }
    dfs(0);
    int sum = 0;
    int v = n - 1;
    maxm = 0;
    while (v != 0) {
        sum += w[ps2[v]];
        maxm = max(maxm, mw[ps2[v]] - w[ps2[v]]);
        v = ps[v];
    }
    cout << sum + maxm << endl;
    return 0;
}
