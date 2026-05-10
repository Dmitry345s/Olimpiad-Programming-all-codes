#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
#define int long long

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    int v;
    cin >> v;
    vector<pair<int, int>> b = {{0, 0}};
    for (int i = 0; i < n; ++i) {
        a[i] = {-a[i].first + a[i].second * v, a[i].first + a[i].second * v};
        if (a[i].first >= 0 && a[i].second >= 0) {
            b.push_back({a[i]});
        }
    }
    sort(a.begin(), a.end());
    vector<int> dp(n + 1, 1e9);
    dp[0] = -1e9;
    for (int i = 0; i < n; ++i) {
        int ch = a[i].second;
        int j = upper_bound(dp.begin(), dp.end(), ch) - dp.begin();
        dp[j] = min(dp[j], ch);
    }
    int ans1 = 0;
    for (int i = n; i >= 0; --i) {
        if (dp[i] != 1e9) {
            ans1 = i;
            break;
        }
    }
    sort(b.begin(), b.end());
    vector<int> dp2(n + 1, 1e9);
    dp2[0] = -1e9;
    for (int i = 0; i < b.size(); ++i) {
        int ch = b[i].second;
        int j = upper_bound(dp2.begin(), dp2.end(), ch) - dp2.begin();
        dp2[j] = min(dp2[j], ch);
    }
    int ans2 = 0;
    for (int i = n; i >= 0; --i) {
        if (dp2[i] != 1e9) {
            ans2 = i;
            break;
        }
    }
    cout << ans2 - 1 << " " << ans1 << endl;
    return 0;
}
