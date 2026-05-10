#include<bits/stdc++.h>

#define int long long

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
    vector<vector<int>> dp(n + 2, vector<int> (k + 1));
    dp[1][0] = 1;
    for (int i = 1; i <= n; ++i) {
        vector<vector<int>> ndp(n + 2, vector<int> (k + 1));
        for (int p = 0; p <= n; ++p) {
            for (int t = 0; t <= k; ++t) {
                if (p - 1 >= 0 && t + rs[i - 1] <= k) ndp[p - 1][t + rs[i - 1]] = (ndp[p - 1][t + rs[i - 1]] + p * dp[p][t]) % MOD;
                if (p + 1 <= n && t <= k) ndp[p + 1][t] = (ndp[p + 1][t] + p * dp[p][t]) % MOD;
                ndp[p][t] = (ndp[p][t] + 2 * p * dp[p][t]) % MOD;
            }
        }
        dp = ndp;
    }
    int ans = 0;
    for (int i = 0; i <= k; ++i) {
        ans = (ans + dp[0][i]) % MOD;
    }
    cout << ans << endl;
    return 0;
}
