#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

signed main() {
    int n, d, t;
    cin >> n >> d >> t;
    vector<int> ts(n);
    for (int i = 0; i < n; ++i) {
        cin >> ts[i];
    }
    vector<pair<int, int>> st;
    vector<int> need(n, n);
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && st.back().first + (i - st.back().second) >= ts[i]) {
            need[st.back().second] = i;
            st.pop_back();
        }
        st.push_back({ts[i], i});
    }
    vector<int> now(n);
    now[0] = ts[0];
    vector<int> pref(n);
    pref[0] = (now[0] <= t);
    for (int i = 1; i < n; ++i) {
        now[i] = min(now[i - 1] + 1, ts[i]);
        pref[i] = pref[i - 1] + (now[i] <= t);
    }
    vector<int> suf(n + 1);
    suf[n - 1] = (ts.back() <= t);
    suf[n] = 0;
    for (int i = n - 2; i >= 0; --i) {
        if (ts[i] > t) {
            suf[i] = suf[i + 1];
        } else {
            int x = t - ts[i];
            int j = min(need[i], i + x + 1);
            //cout << i << " " << j << endl;
            suf[i] = suf[j] + (j - i);
        }
        //cout << suf[i] << " ";
    }
    //cout << endl;
    int ans = min(pref[n - 1], suf[0]);
    for (int i = 0; i < n - 1; ++i) {
        ans = min(ans, pref[i] + suf[i + 1]);
    }
    cout << ans << endl;
    /*vector<vector<int>> dp(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        vector<int> now;
        now.push_back(ts[i]);
        dp[i][i] = (now.back() <= t);
        for (int j = i + 1; j < n; ++j) {
            now.push_back(min(now.back() + 1, ts[j]));
            dp[i][j] = dp[i][j - 1] + (now.back() <= t);
            //cout << i << " " << j << " " << dp[i][j] << endl;
        }
    }
    d = min(d, n + 1);
    vector<vector<int>> ans(n, vector<int> (d + 2, INF));
    for (int i = 0; i < n; ++i) {
        ans[i][1] = dp[0][i];
    }
    for (int i = 0; i < n; ++i) {
        for (int k = 2; k < d + 2; ++k) {
            for (int j = 0; j < i; ++j) {
                ans[i][k] = min(ans[i][k], ans[j][k - 1] + dp[j + 1][i]);
            }
        }
    }
    int rans = INF;
    for (int i = 0; i < n; ++i) {
        rans = min(rans, ans[i][d] + dp[i][n - 1]);
    }
    cout << ans[n - 1][d + 1] << endl;*/
    return 0;
}
