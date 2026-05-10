#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<int> cl(n + 1), cr(m + 1);
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> cl[i];
        ans = max(ans, cl[i]);
    }
    for (int i = 1; i <= m; ++i) {
        cin >> cr[i];
        ans = max(ans, cr[i]);
    }
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < p; ++i) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    for (int i = 1; i <= n; ++i) {
        sort(g[i].begin(), g[i].end());
    }
    vector<int> dl(n + 1), dr(m + 1);
    dl = cl;
    dr = cr;
    for (int i = 1; i <= n; ++i) {
        for (int to : g[i]) {
            int k = dl[i];
            dl[i] = max(k, cl[i] + dr[to]);
            ans = max(ans, dl[i]);
            dr[to] = max(dr[to], k + cr[to]);
            ans = max(ans, dr[to]);
        }
    }
    cout << ans << endl;
    return 0;
}
