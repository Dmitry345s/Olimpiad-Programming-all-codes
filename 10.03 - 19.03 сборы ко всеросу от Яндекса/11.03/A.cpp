#include<bits/stdc++.h>

#pragma GCC optmize("O3")

#define int long long

using namespace std;

const int INF = 2e18;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
        all[i].first += all[i].second;
    }
    sort(all.begin(), all.end());
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        int k = upper_bound(dp.begin(), dp.end(), all[i].first - all[i].second) - dp.begin();
        --k;
        for (int j = min(i, k) + 1; j > 0; --j) {
            bool u = dp[j] - dp[j - 1] >  + all[i].second;
            dp[j] = u * (dp[j - 1] + all[i].second) + (!u) * dp[j];
        }
    }
    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        if (dp[i] < INF) {
            ans = i;
        }
    }
    cout << ans << endl;
    return 0;
}
