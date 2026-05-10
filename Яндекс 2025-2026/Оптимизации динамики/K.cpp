#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 2e5 + 1;
int a[MAX];

pair<int, int> ch(int lm, int n) {
    vector<array<pair<int, int>, 2>> dp(n);
    dp[0] = {pair<int, int>{-lm, 1}, pair<int, int>{0, 0}};
    for (int i = 1; i < n; ++i) {
        dp[i][0] = max(pair<int, int>{dp[i - 1][0].first - lm, dp[i - 1][0].second + 1},
                       pair<int, int>{dp[i - 1][1].first - lm + a[i - 1], dp[i - 1][1].second + 1});
        dp[i][1] = max(pair<int, int>{dp[i - 1][0].first + a[i - 1], dp[i - 1][0].second},
                       pair<int, int>{dp[i - 1][1].first, dp[i - 1][1].second});
    }
    return max(dp[n - 1][0], dp[n - 1][1]);
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        cin >> a[i];
    }
    int l = -1e10, r = 1e10;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        pair<int, int> now = ch(c, n);
        if (now.second >= m) {
            l = c;
        } else {
            r = c;
        }
    }
    cout << ch(l, n).first + m * l << endl;
    return 0;
}
