#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<int>> jf(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        vector<int> ch(n + 1, 1e9);
        ch[0] = -1e9;
        int now = 0;
        for (int j = i; j < n; ++j) {
            int k = lower_bound(ch.begin(), ch.end(), a[j]) - ch.begin();
            ch[k] = a[j];
            now = max(now, k);
            jf[i][j] = now;
        }
    }
    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << jf[i][j] << " ";
        }
        cout << endl;
    }*/
    for (int k = 1; k <= n; ++k) {
        vector<vector<int>> dp(n, vector<int> (n, 1e9));
        for (int len = 0; len < n; ++len) {
            for (int l = 0; l < n - len; ++l) {
                int r = l + len;
                if (jf[l][r] >= k) {
                    dp[l][r] = min(dp[l][r], r - l + 1 - jf[l][r]);
                }
                for (int c = l; c < r; ++c) {
                    dp[l][r] = min(dp[l][r], dp[l][c] + dp[c + 1][r]);
                }
            }
        }
        cout << max(0, n - dp[0][n - 1]) << " ";
    }
    return 0;
}
