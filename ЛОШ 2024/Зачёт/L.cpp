#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> pref(n);
    pref[0] = a[0];
    for (int i = 1; i < n; ++i) {
        pref[i] = pref[i - 1] + a[i];
    }
    int ls = min(pref.back(), pref.back() / n + n);
    //ls = pref.back();
    vector<vector<int>> dp(pref.back() + 1, vector<int> (ls + 1, 1e9));
    vector<vector<int>> ndp(pref.back() + 1, vector<int> (ls + 1, 1e9));
    //vector<vector<int>> ch(pref.back() + 1, vector<int> (ls + 1, 1e9));
    //cout << ls << endl;
    for (int i = 0; i <= ls; ++i) {
        dp[i][i] = abs(pref[0] - i);
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= pref.back(); ++j) {
            for (int k = 0; k <= ls; ++k) {
                if (k > j) continue;
                int v = dp[j - k][k];
                if (k != ls) {
                    v = min(v, dp[j - k][k + 1]);
                }
                if (k != 0) {
                    v = min(v, dp[j - k][k - 1]);
                }
                ndp[j][k] = min((int)1e9, v + abs(pref[i] - j));
            }
        }
        dp = ndp;
    }
    int ans = 1e9;
    for (int i = 0; i <= ls; ++i) {
        ans = min(ans, dp[pref.back()][i]);
    }
    cout << ans << endl;
    return 0;
}
