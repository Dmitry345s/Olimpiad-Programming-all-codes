#include<bits/stdc++.h>

# define int long long

using namespace std;

pair<int, int> check(int sc, vector<int> a, int n) {
    vector<vector<pair<int, int>>> dp(n, vector<pair<int, int>> (2, pair<int, int>{-1, -1}));
    dp[0][0] = {0, 0};
    dp[0][1] = {-sc, 1};
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][0];
        if (dp[i - 1][1].first + a[i - 1] > dp[i][0].first ||
            (dp[i - 1][1].first + a[i - 1] == dp[i][0].first) && (dp[i - 1][1].second < dp[i][0].second)) {
            dp[i][0] = {dp[i - 1][1].first + a[i - 1], dp[i - 1][1].second};
        }
        dp[i][1] = dp[i - 1][1];
        if (dp[i - 1][0].first + a[i - 1] > dp[i][1].first ||
            (dp[i - 1][0].first + a[i - 1] == dp[i][1].first) && (dp[i - 1][0].second < dp[i][1].second)) {
            dp[i][1] = {dp[i - 1][0].first + a[i - 1], dp[i - 1][0].second};
        }
        dp[i][1].first -= sc;
        dp[i][1].second += 1;
    }
    if (dp.back()[0].first > dp.back()[1].first ||
        (dp.back()[0].first == dp.back()[1].first && dp.back()[0].second < dp.back()[1].second)) {
        return dp.back()[0];
    }
    return dp.back()[1];
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> a[i];
    }
    if (m > n / 2) {
        m = n - m;
    }
    int l = -1, r = (int)2e10;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        pair<int, int> now = check(c, a, n);
        //cout << c << endl;
        //cout << now.first << " " << now.second << endl;
        if (now.second <= m) {
            r = c;
        } else {
            l = c;
        }
    }
    //cout << r << endl;
    cout << check(r, a, n).first + r * m << endl;
    return 0;
}
