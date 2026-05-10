#include<bits/stdc++.h>

using namespace std;

void get(vector<vector<int>> & opt, int l, int r, vector<string> & ans) {
    if (l == r) return;
    for (int i = l; i <= opt[l][r]; ++i) {
        ans[i].push_back('0');
    }
    for (int i = opt[l][r] + 1; i <= r; ++i) {
        ans[i].push_back('1');
    }
    get(opt, l, opt[l][r], ans);
    get(opt, opt[l][r] + 1, r, ans);
}

signed main() {
    freopen("codes.in", "r", stdin);
    freopen("codes.out", "w", stdout);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<vector<long long>> dp(n, vector<long long> (n, (long long)1e18));
    vector<vector<int>> opt(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    vector<long long> pr(n + 1);
    for (int i = 1; i <= n; ++i) {
        pr[i] = pr[i - 1] + a[i - 1];
    }
    for (int d = 2; d <= n; ++d) {
        for (int l = 0; l < n; ++l) {
            int r = l + d - 1;
            if (r >= n) continue;
            for (int c = max(l, opt[l][r - 1]); c <= min(r - 1, opt[l + 1][r]); ++c) {
                long long cur = dp[l][c] + dp[c + 1][r] + pr[r + 1] - pr[l];
                dp[l][r] = min(dp[l][r], cur);
                if (dp[l][r] == cur) {
                    opt[l][r] = c;
                }
            }
            //cout << l << " " << r << " " << dp[l][r] << endl;
        }
    }
    vector<string> ans(n);
    get(opt, 0, n - 1, ans);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
