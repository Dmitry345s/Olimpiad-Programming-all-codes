#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int k, n, m;
    cin >> k >> n >> m;
    vector<vector<int>> a(k + 1);
    for (int i = 0; i < n; ++i) {
        int ch, t;
        cin >> ch >> t;
        a[t].push_back(ch);
    }
    vector<int> fc;
    int MAX = 1e18;
    int cnt = 0;
    int ans = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        if ((int)a[i].size() != 0) {
            cnt++;
        }
        for (int j = 1; j < (int)a[i].size(); ++j) {
            fc.push_back(a[i][j] - a[i][j - 1]);
            ans += fc.back();
        }
    }
    if (cnt > m) {
        cout << -1 << endl;
        return 0;
    }
    m -= cnt;
    sort(fc.rbegin(), fc.rend());
    for (int i = 0; i < m; ++i) {
        ans -= fc[i];
    }
    cout << ans << endl;
    return 0;
}
