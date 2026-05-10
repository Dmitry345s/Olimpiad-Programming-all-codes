#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i + 1];
    }
    if (k == 1) {
        int maxm = 0;
        for (int i = 1; i <= n; ++i) {
            maxm = max(maxm, a[i]);
        }
        long long ans = 0;
        for (int i = 1; i <= n; ++i) {
            ans += maxm - a[i];
        }
        cout << ans << endl;
        return 0;
    } else if (k == 2) {
        int maxm = 0;
        vector<int> pref(n + 1);
        pref[0] = 0;
        for (int i = 1; i <= n; ++i) {
            pref[i] = pref[i - 1];
            if (a[i] > maxm) {
                pref[i] += (a[i] - maxm) * (i - 1);
                maxm = a[i];
            } else {
                pref[i] += maxm - a[i];
            }
            //cout << pref[i] << endl;
        }
        maxm = 0;
        vector<int> suf(n + 1);
        suf[n] = 0;
        for (int i = n - 1; i >= 0; --i) {
            suf[i] = suf[i + 1];
            if (a[i + 1] > maxm) {
                suf[i] += (a[i + 1] - maxm) * (n - i - 1);
                maxm = a[i + 1];
            } else {
                suf[i] += maxm - a[i + 1];
            }
            //cout << i << " " << suf[i] << endl;
        }
        int ans = 1e15;
        for (int i = 1; i < n; ++i) {
            ans = min(ans, pref[i] + suf[i]);
        }
        cout << ans << endl;
        return 0;
    }
    vector<vector<array<int, 3>>> dp(n + 1, vector<array<int, 3>> (k + 1, {(int)1e15, (int)1e9, (int)1e9}));
    dp[0][0] = {0, 0, 0};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            //cout << dp[i][j][0] << " " << dp[i][j][1] << " " << dp[i][j][2] << " " << i << " " << j << endl;
            if (j != k) {
                dp[i + 1][j + 1] = min(dp[i + 1][j + 1], array<int, 3>{dp[i][j][0], 1ll, 0ll});
            }
            if (i != 0 && j != 0) {
                dp[i + 1][j] = min(dp[i + 1][j], array<int, 3>{(a[i + 1] - a[i]) * dp[i][j][1] + dp[i][j][0], dp[i][j][1] + 1, (a[i + 1] - a[i]) * dp[i][j][1] + dp[i][j][2]});
            }
        }
    }
    cout << dp[n][k][0] << endl;
    return 0;
}
