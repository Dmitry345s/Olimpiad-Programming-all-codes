#include<bits/stdc++.h>

# define int long long

using namespace std;

const int INF = 2e18, MAX = 2e3 + 1;

vector<string> ans(MAX);

void to_get(int l, int r, vector<vector<int>> & opt) {
    if (l == r) return;
    //cout << l << " " << r << endl;
    for (int i = l; i <= opt[l][r]; ++i) {
        ans[i].push_back('0');
    }
    for (int i = opt[l][r] + 1; i <= r; ++i) {
        ans[i].push_back('1');
    }
    to_get(l, opt[l][r], opt);
    to_get(opt[l][r] + 1, r, opt);
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + a[i - 1];
    }
    vector<vector<int>> dp(n, vector<int> (n, INF));
    vector<vector<int>> opt(n, vector<int> (n, -1));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for (int d = 2; d <= n; ++d) {
        //cout << d << endl;
        for (int l = 0; l < n; ++l) {
            int r = (l + d - 1);
            if (r >= n) break;
            for (int c = opt[l][r - 1]; c <= min(r - 1, opt[l + 1][r]); ++c) {
                if (dp[l][c] + dp[c + 1][r] < dp[l][r]) {
                    dp[l][r] = dp[l][c] + dp[c + 1][r];
                    opt[l][r] = c;
                }
            }
            //cout << l << " " << r << " " << dp[l][r] << endl;
            //cout << l << " " << r << " " << opt[l][r] << endl;
            dp[l][r] += pref[r + 1] - pref[l];
        }
    }
    //cout << 0 << endl;
    to_get(0, n - 1, opt);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
