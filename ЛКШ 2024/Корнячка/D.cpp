#include<bits/stdc++.h>

using namespace std;

const int MOD = 998244353, K = 500;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> dp(n);
    vector<vector<int>> cnt(K);
    for (int i = 0; i < K; ++i) {
        cnt[i].assign(i, 0);
    }
    dp[0] = 1;
    for (int i = 0; i < n; ++i) {
        //cout << i << endl;
        for (int j = 1; j < K; ++j) {
            dp[i] += cnt[j][i % j];
            dp[i] %= MOD;
        }
        if (a[i] < K) {
            cnt[a[i]][i % a[i]] += dp[i];
            cnt[a[i]][i % a[i]] %= MOD;
        } else {
            for (int j = i + a[i]; j < n; j += a[i]) {
                dp[j] += dp[i];
                dp[j] %= MOD;
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        ans += dp[i];
        ans %= MOD;
    }
    cout << ans << endl;
    return 0;
}
