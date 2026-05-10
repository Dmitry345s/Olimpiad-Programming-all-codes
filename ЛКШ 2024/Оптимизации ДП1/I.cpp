#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        vector<vector<int>> dp(n, vector<int> (n, (int)1e9));
        vector<vector<int>> opt(n, vector<int> (n));
        for (int i = 0; i < n; ++i) {
            dp[i][i] = 0;
        }
        vector<int> pr(n + 1);
        pr[0] = 0;
        for (int i = 1; i <= n; ++i) {
            pr[i] = pr[i - 1] + a[i - 1];
            //cout << pr[i] << endl;
        }
        for (int d = 2; d <= n; ++d) {
            for (int l = 0; l < n; ++l) {
                if (l + d - 1 >= n) continue;
                int r = l + d - 1;
                for (int c = max(opt[l][r - 1], l + 1); c <= min(r - 1, opt[l + 1][r]); ++c) {
                    int cur = dp[l][c - 1] + dp[c + 1][r] + pr[c] - pr[l] + pr[r + 1] - pr[c + 1];
                    dp[l][r] = min(dp[l][r], cur);
                    if (dp[l][r] == cur) {
                        opt[l][r] = c;
                    }
                }
                if (dp[l + 1][r] + pr[r + 1] - pr[l + 1] < dp[l][r]) {
                    dp[l][r] = dp[l + 1][r] + pr[r + 1] - pr[l + 1];
                    opt[l][r] = l;
                }
                if (dp[l][r - 1] + pr[r] - pr[l] < dp[l][r]) {
                    dp[l][r] = dp[l][r - 1] + pr[r] - pr[l];
                    opt[l][r] = r;
                }
            }
        }
        cout << dp[0][n - 1] << endl;
    }
    return 0;
}
