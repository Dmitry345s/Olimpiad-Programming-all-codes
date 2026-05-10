#include<bits/stdc++.h>

# define int long long

using namespace std;

const int INF = 1e18;

signed main() {
    int n, b, c;
    cin >> n >> c >> b;
    vector<int> t(n);
    for (int i = 0; i < n; ++i) {
        cin >> t[i];
    }
    vector<int> g(n);
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    vector<int> dp(n + 1, INF);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        int now = 0;
        int ans = dp[i];
        for (int j = i; j < n; ++j) {
            now += g[j];
            ans += now / c * (b + t[j]) + t[j] * (now % c != 0);
            now %= c;
            dp[j + 1] = min(dp[j + 1], ans + (now != 0) * b);
        }
    }
    cout << dp[n] << endl;
}
