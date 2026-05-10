#include<bits/stdc++.h>

using namespace std;

const long long INF = 1e10;

pair<long long, long long> checker(long long x, vector<long long> a) {
    int n = (int)a.size();
    vector<pair<long long, long long>> dp(n, pair<long long, long long> {INF, INF});
    dp[0] = {0, 0};
    dp[1] = {a[1] - a[0] - x, 1};
    if (0 < dp[1].first || 0 == dp[1].first && dp[0].second < dp[1].second) {
        dp[1] = {0, 0};
    }
    for (int i = 2; i < n; ++i) {
        pair<long long, long long> p1 = {dp[i - 2].first + a[i] - a[i - 1] - x, dp[i - 2].second + 1};
        pair<long long, long long> p2 = {dp[i - 1].first, dp[i - 1].second};
        dp[i] = p2;
        if (p1.first < p2.first || p1.first == p2.first && p1.second > p2.second) {
            dp[i] = p1;
        }
    }
    return dp.back();
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<long long> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    long long l = -1, r = 2e9;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        pair<long long, long long> to_ans = checker(m, a);
        if (to_ans.second < k) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << checker(r, a).first + r * k << endl;
    return 0;
}
