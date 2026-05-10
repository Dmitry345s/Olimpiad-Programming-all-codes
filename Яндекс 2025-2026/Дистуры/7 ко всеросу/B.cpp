#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e18 + 1;

signed main() {
    int n;
    cin >> n;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];
    }
    vector<int> pr(n, -1);
    vector<pair<int, int>> st;
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && st.back().first <= y[i]) {
            pr[st.back().second] = i;
            st.pop_back();
        }
        st.push_back({y[i], i});
    }
    st.clear();
    int l = 0, r = INF;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        vector<int> dp(n);
        dp[0] = 1;
        for (int i = 1; i < n; ++i) {
            int u = pr[i];
            int now = i - 1;
            while (now >= 0 && now >= u) {
                int dx = (x[i] - x[now]);
                int dy = (y[i] - y[now]);
                int dist = dx * dx + dy * dy;
                if (dist <= m) {
                    dp[i] |= dp[now];
                }
                now = pr[now];
            }
        }
        if (dp[n - 1]) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << setprecision(30) << sqrtl(r) << endl;
    return 0;
}
