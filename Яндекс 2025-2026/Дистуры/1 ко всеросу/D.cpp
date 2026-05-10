#include<bits/stdc++.h>

using namespace std;

const int C = 41;

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> dp(n + 1, vector<int> (C));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < a[i]; ++j) {
            dp[i][j] = i;
        }
        dp[i][a[i]] = i + 1;
    }
    for (int j = 0; j < C; ++j) {
        dp[n][j] = n;
    }
    for (int j = 1; j < C; ++j) {
        for (int i = 0; i < n; ++i) {
            if (j == a[i]) continue;
            dp[i][j] = dp[dp[i][j - 1]][j - 1];
            //cout << i << " " << j << " " << dp[i][j] << endl;
        }
    }
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        int j = lower_bound(dp[l].begin(), dp[l].end(), r) - dp[l].begin();
        cout << j << endl;
    }
    return 0;
}
