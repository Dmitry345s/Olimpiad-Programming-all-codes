#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(2 * n + 2);
    for (int i = 0; i < k; ++i) {
        int l, r;
        cin >> l >> r;
        for (int j = l; j <= r; ++j) {
            a[j] = 1;
        }
    }
    if (n <= 3000) {
        vector<vector<int>> dp(n + 1, vector<int> (n + 1, 1e18));
        vector<int> ch1(n + 1, 1e18), ch2(n + 1, 1e18);
        dp[0][0] = 0;
        for (int i = 0; i < n + 1; ++i) {
            for (int j = 0; j < n + 1; ++j) {
                dp[i][j] = min(dp[i][j], min(ch1[i], ch2[j]));
                if (dp[i][j] % 2 == 1) {
                    ch1[i] = min(ch1[i], dp[i][j]);
                } else if (a[i + j]) {
                    ch1[i] = min(ch1[i], dp[i][j] + 1);
                }
                if (dp[i][j] % 2 == 0) {
                    ch2[j] = min(ch2[j], dp[i][j]);
                } else if (a[i + j]) {
                    ch2[j] = min(ch2[j], dp[i][j] + 1);
                }
            }
        }
        if (dp[n][n] != 1e18) {
            cout << "Full" << endl;
            cout << dp[n][n] << endl;
        } else {
            cout << "Hungry" << endl;
        }
        return 0;
    }
    if (a[n]) {
        cout << "Full" << endl;
        cout << 1 << endl;
        return 0;
    }
    for (int i = 0; i <= n; ++i) {
        if (a[i] && a[i + n]) {
            cout << "Full" << endl;
            cout << 2 << endl;
            return 0;
        }
    }
    cout << "Hungry" << endl;
    return 0;
}
