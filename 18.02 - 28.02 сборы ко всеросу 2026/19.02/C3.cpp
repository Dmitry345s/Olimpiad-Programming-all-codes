#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
    }
    vector<int> s(n), rs(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
        rs[p[i]] = s[i];
    }
    if (rs[n - 1] > k) {
        cout << 0 << endl;
        return 0;
    }
    vector<vector<int>> dp(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }
    for (int d = 2; d <= n; ++d) {
        for (int l = 0; l < n; ++l) {
            int r = l + d - 1;
            if (r >= n) break;
            dp[l][r] = (dp[l + 1][r] + dp[l][r - 1]) % MOD;
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}
