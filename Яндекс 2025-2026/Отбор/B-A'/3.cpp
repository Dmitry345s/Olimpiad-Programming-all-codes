#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

signed main() {
    int n;
    cin >> n;
    vector<int> p(n);
    vector<int> q(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> q[i];
    }
    vector<array<int, 2>> dp1(n);
    dp1[0][0] = p[0];
    dp1[0][1] = INF;
    for (int i = 1; i < n; ++i) {
        dp1[i][0] = min(dp1[i - 1][0] + q[i - 1], dp1[i - 1][1]) + p[i];
        dp1[i][1] = min(dp1[i - 1][0], dp1[i - 1][1] + q[i - 1]);
    }
    int ans = INF;
    ans = min(ans, min(dp1[n - 1][0] + q[n - 1], dp1[n - 1][1]));
    dp1[0][0] = INF;
    dp1[0][1] = 0;
    for (int i = 1; i < n; ++i) {
        dp1[i][0] = min(dp1[i - 1][0] + q[i - 1], dp1[i - 1][1]) + p[i];
        dp1[i][1] = min(dp1[i - 1][0], dp1[i - 1][1] + q[i - 1]);
    }
    ans = min(ans, min(dp1[n - 1][0], dp1[n - 1][1] + q[n - 1]));
    cout << ans << endl;
}
