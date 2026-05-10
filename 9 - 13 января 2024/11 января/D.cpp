#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, q;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> q;
    if (n <= 30000) {
        vector<vector<int>> dp1(n, vector<int> (n));
        for (int i = 0; i < n; ++i) {
            int minm = 1e9, maxm = -1e9;
            for (int j = i; j < n; ++j) {
                minm = min(minm, a[j]);
                maxm = max(maxm, a[j]);
                if (min(a[i], a[j]) == minm && max(a[i], a[j]) == maxm) {
                    dp1[i][j] = 1;
                }
            }
        }
        vector<vector<int>> dp(n, vector<int> (n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 1;
        }
        for (int d = 2; d <= n; ++d) {
            for (int l = 0; l <= n - d; ++l) {
                int r = l + d - 1;
                dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
                //cout << l << " " << r << " " << dp[l + 1][r] << " " << dp[l][r - 1] << endl;
                if (dp1[l][r]) {
                    dp[l][r] = d;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i; j < n; ++j) {
                //cout << i << " " << j << " " << dp[i][j] << endl;
            }
        }
        for (int i = 0; i < q; ++i) {
            int l, r;
            cin >> l >> r;
            --l; --r;
            cout << dp[l][r] << endl;
        }
    }
    return 0;
}
