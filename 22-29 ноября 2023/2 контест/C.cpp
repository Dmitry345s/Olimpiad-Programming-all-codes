#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(k + 1, vector<int> (n + 1));
    vector<int> pref(n + 1), pref2(n + 1);
    int mod = 1e9 + 7;
    dp[1][n] = 1;
    pref[0] = 0;
    pref2[1] = 0;
    for (int j = 2; j <= n; ++j) {
        pref[j] = pref[j - 1];
        pref2[j] = pref2[j - 1];
        if (j % 2 == 0) {
            pref[j] += dp[1][j];
            pref[j] %= mod;
        } else {
            pref2[j] += dp[1][j];
            pref2[j] %= mod;
        }
    }
    dp[2][n - 1] = 1;
    for (int i = 3; i <= k; ++i) {
        for (int j = n; j >= 1; --j) {
            if (j % 2 == 0) {
                dp[i][j] += ((pref[n] - pref[j]) % mod + mod) % mod;
                dp[i][j] %= mod;
            } else {
                dp[i][j] += ((pref2[n] - pref2[j]) % mod + mod) % mod;
                dp[i][j] %= mod;
            }
            if (j + i - 1 > n) {
                continue;
            }
            if ((j + i - 1) % 2 == 0) {
                dp[i][j] += ((pref2[n] - pref2[j + i - 1]) % mod + mod) % mod;
                dp[i][j] %= mod;
            } else {
                dp[i][j] += ((pref[n] - pref[j + i - 1]) % mod + mod) % mod;
                dp[i][j] %= mod;
            }
        }
        pref[0] = dp[i][0];
        pref2[1] = dp[i][1];
        for (int j = 2; j <= n; ++j) {
            pref[j] = pref[j - 1];
            pref2[j] = pref2[j - 1];
            if (j % 2 == 0) {
                pref[j] += dp[i][j];
                pref[j] %= mod;
            } else {
                pref2[j] += dp[i][j];
                pref2[j] %= mod;
            }
        }
    }
    /*for (int i = 1; i <= k; ++i) {
        for (int j = n; j >= 1; --j) {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }*/
    long long ans = 0;
    for (int i = 2; i <= k; ++i) {
        long long sum = 0;
        for (int j = 1; j <= n; ++j) {
            sum = (sum + dp[i][j]) % mod;
        }
        ans += (k - i + 1) * sum;
        ans %= mod;
    }
    cout << (ans * 2) % mod << endl;
    return 0;
}
