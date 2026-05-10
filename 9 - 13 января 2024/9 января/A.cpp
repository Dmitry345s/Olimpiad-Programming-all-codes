#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> u, u2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a;
            cin >> a;
            if (a) {
                u.push_back({i, j});
                u2.push_back({j, i});
            }
        }
    }
    sort(u.begin(), u.end());
    sort(u2.begin(), u2.end());
    long long ans = 0;
    if (u[0].first != u[1].first) {
        ans = max(u[1].first * m, (n - u[0].first - 1) * m);
    }
    if (u2[0].first != u2[1].first) {
        ans = max(ans, max(u2[1].first * n, (m - u2[0].first - 1) * n));
    }
    cout << ans << endl;
    return 0;
}
