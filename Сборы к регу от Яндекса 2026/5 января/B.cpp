#include<bits/stdc++.h>

using namespace std;

int ch(int x, vector<pair<int, int>> all, int h) {
    int n = (int)all.size();
    vector<int> dp(n + 1);
    dp[0] = 0;
    for (int i = 1; i <= n; ++i) {
        dp[i] = all[i - 1].second;
    }
    int mx = dp[1];
    for (int i = 1; i < n; ++i) {
        if (all[i].first - all[i - 1].first <= x) {
            dp[i + 1] = max(dp[i + 1], dp[i] + all[i].second);
        }
        mx = max(mx, dp[i + 1]);
    }
    return mx >= h;
}

const int INF = 1e9 + 5;

signed main() {
    int n, H;
    cin >> n >> H;
    vector<int> h(n), w(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> w[i];
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) all[i] = {h[i], w[i]};
    sort(all.begin(), all.end());
    int l = -1, r = INF;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (ch(m, all, H)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << r << endl;
    return 0;
}
