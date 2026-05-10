#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e18;

signed main() {
    int x, n, m, w, t;
    cin >> x >> n >> m >> w >> t;
    vector<int> s(n);
    for (int i = 0; i < n; ++i) {
        cin >> s[i];
    }
    s.push_back(-1);
    s.push_back(x);
    sort(s.begin(), s.end());
    vector<pair<int, int>> all(m);
    for (int i = 0; i < m; ++i) {
        cin >> all[i].first >> all[i].second;
    }
    sort(all.begin(), all.end());
    vector<vector<int>> dp(n + 2, vector<int> (1 << m, INF));
    dp[0][0] = 0;
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < (1 << m); ++j) {
            int u = s[i + 1] / t * t;
            int y = - s[i] % t;
            if (y < 0) y += t;
            int nowcnt = dp[i][j] + w * ((max(0ll, (s[i + 1] - s[i] - y)) + t - 1) / t);
            for (int tt = 0; tt < m; ++tt) {
                if (!((j >> tt) & 1)) {
                    int y = all[tt].first - s[i] % t;
                    if (y < 0) y += t;
                    nowcnt += w * ((max(0ll, (s[i + 1] - s[i] - y)) + t - 1) / t);
                }
            }
            dp[i + 1][j] = min(dp[i + 1][j], nowcnt);
            int en = s[i + 1] % t;
            int ms = j;
            for (int tt = m - 1; tt >= 0; --tt) {
                if (all[tt].first > en) continue;
                if ((j >> tt & 1)) continue;
                ms += (1 << tt);
                nowcnt -= w;
                dp[i + 1][ms] = min(dp[i + 1][ms], nowcnt);
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < (1 << m); ++i) {
        int nans = dp.back()[i];
        for (int j = 0; j < m; ++j) {
            if ((i >> j) & 1) {
                nans += all[j].second;
            }
        }
        ans = min(ans, nans);
    }
    cout << ans << endl;
    return 0;
}
