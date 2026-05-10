#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 2e5, LN = 32;
vector<int> pref[MAX], in[MAX];
int a[MAX];

pair<int, int> solve(int lb, int n) {
    vector<pair<int, int>> dp(n + 1, {-1, 2 * MAX});
    dp[0] = {0, 0};
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < LN; ++j) {
            int now = dp[in[i - 1][j]].first + pref[i - 1][j] - lb;
            if (in[i - 1][j] == 0 && dp[i].second == 2 * MAX) {
                dp[i] = {now, 1};
                continue;
            }
            if (now > dp[i].first ||
                (now == dp[i].first && dp[in[i - 1][j]].second + 1 < dp[i].second)) {
                dp[i] = {now, dp[in[i - 1][j]].second + 1};
            }
        }
    }
    return dp.back();
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> fpref(LN, 0);
    vector<int> fin(LN, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < LN; ++j) {
            if ((a[i] >> j) & 1) {
                fin[j] = i;
                fpref[j] = a[i];
            } else {
                fpref[j] |= a[i];
            }
        }
        pref[i] = fpref;
        in[i] = fin;
    }
    int l = -1, r = 1e18;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        pair<int, int> now = solve(m, n);
        if (now.second <= k) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << solve(r, n).first + r * k << endl;
    return 0;
}
