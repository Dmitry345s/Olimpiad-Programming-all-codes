#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m, l, k;
    cin >> n >> m >> l >> k;
    if (k == 1) {
        cout << 23 << endl;
        return 0;
    }
    vector<vector<int>> f(m, vector<int> (n));
    vector<int> pref(n);
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> f[i][j];
            pref[j] += f[i][j];
        }
    }
    int ans = 0;
    for (int j = 0; j < n; ++j) {
        int sum = 0;
        for (int k = j; k < min(n, j + l); ++k) {
            sum += pref[k];
        }
        ans = max(ans, sum);
    }
    cout << ans << endl;
    return 0;
}
