#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

pair<int, int> ch(int x, vector<int> & a) {
    int n = (int)a.size();
    vector<array<pair<__int128, int>, 2>> dp(n + 1);
    dp[0][0] = {-x, 1};
    dp[0][1] = {0, 0};
    for (int i = 1; i <= n; ++i) {
        int u = a[i - 1];
        if (dp[i - 1][0].first - x > dp[i - 1][1].first - x + u) {
            dp[i][0] = dp[i - 1][0];
            dp[i][0].first -= x;
            dp[i][0].second += 1;
        } else if (dp[i - 1][0].first - x < dp[i - 1][1].first - x + u) {
            dp[i][0] = dp[i - 1][1];
            dp[i][0].first -= x - u;
            dp[i][0].second += 1;
        } else {
            dp[i][0].first = dp[i - 1][0].first - x;
            dp[i][0].second = max(dp[i - 1][0].second, dp[i - 1][1].second) + 1;
        }
        dp[i][1] = dp[i - 1][0];
        dp[i][1].first += u;
        dp[i][1] = max(dp[i][1], dp[i - 1][1]);
    }
    return max(dp.back()[0], dp.back()[1]);
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> a[i];
    }
    int l = -INF, r = INF;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        pair<int, int> now_ch = ch(c, a);
        if (now_ch.second < m) {
            r = c;
        } else {
            l = c;
        }
    }
    pair<int, int> ans = ch(l, a);
    cout << ans.first + l * m << endl;
    return 0;
}
