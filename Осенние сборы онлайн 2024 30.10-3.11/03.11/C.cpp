#include<bits/stdc++.h>

using namespace std;

const int INF = 2e18;

signed main () {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> x(n - 1);
        for (int i = 0; i < n - 1; ++i) {
            cin >> x[i];
        }
        vector<int> pref(n);
        pref[0] = 0;
        for (int i = 1; i < n; ++i) {
            pref[i] = pref[i - 1] + x[i - 1];
        }
        int last = -1, last2 = -1;
        vector<pair<int, int>> bef(n);
        for (int i = 0; i < n; ++i) {
            if (s[i] == 'A') {
                last = i;
            } else {
                last2 = i;
            }
            bef[i] = {last, last2};
        }
        last = n, last2 = n;
        vector<pair<int, int>> bef(n);
        for (int i = n - 1; i >= 0; --i) {
            if (s[i] == 'A') {
                last = i;
            } else {
                last2 = i;
            }
            aft[i] = {last, last2};
        }
        vector<pair<int, int>> whr(n, INF);
        for (int i = 0; i < n; ++i) {
            if (bef[i].first != -1) {
                whr[i].first = min(whr[i].first, pref[i] - pref[bef[i].first]);
            }
            if (aft[i].first != -1) {
                whr[i].first = min(whr[i].first, pref[i] - pref[aft[i].first]);
            }
            if (bef[i].second != -1) {
                whr[i].second = min(whr[i].second, pref[i] - pref[bef[i].second]);
            }
            if (aft[i].second != -1) {
                whr[i].second = min(whr[i].second, pref[i] - pref[aft[i].second]);
            }
        }
        vector<pair<int, int>> dp(n, {INF, INF});
        dp[0] = whr[0];
        for (int i = 1; i < n; ++i) {
            dp[i].first = min(dp[i].first, dp[i - 1].second + whr[i].first);
            dp[i].second = min(dp[i].first, min(dp[i - 1].first, dp[i - 1].second) + whr[i].second);
        }
    }
    return 0;
}
