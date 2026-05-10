#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> t(2 * n), p(2 * n);
    vector<int> w(n + 1), b(n + 1);
    for (int i = 0; i < 2 * n; ++i) {
        char q;
        cin >> q >> p[i];
        if (q == 'W') {
            t[i] = 0;
            w[p[i]] = i;
        } else {
            t[i] = 1;
            b[p[i]] = i;
        }
    }
    vector<pair<vector<int>, vector<int>>> bef(2 * n);
    bef[0].first = {};
    bef[0].second = {};
    for (int i = 1; i < 2 * n; ++i) {
        bef[i].first = bef[i - 1].first;
        bef[i].second = bef[i - 1].second;
        if (t[i - 1]) {
            bef[i].second.push_back(p[i - 1]);
            sort(bef[i].second.begin(), bef[i].second.end());
        } else {
            bef[i].first.push_back(p[i - 1]);
            sort(bef[i].first.begin(), bef[i].first.end());
        }
    }
    vector<vector<int>> dp(n + 1, vector<int> (n + 1, 1e9));
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = 0;
                continue;
            }
            if (i != 0) {
                int in = w[i];
                int col1 = upper_bound(bef[in].first.begin(), bef[in].first.end(), i - 1) - bef[in].first.begin();
                int col2 = upper_bound(bef[in].second.begin(), bef[in].second.end(), j) - bef[in].second.begin();
                dp[i][j] = min(dp[i][j], dp[i - 1][j] + in - col1 - col2);
            }
            if (j != 0) {
                int in = b[j];
                int col1 = upper_bound(bef[in].first.begin(), bef[in].first.end(), i) - bef[in].first.begin();
                int col2 = upper_bound(bef[in].second.begin(), bef[in].second.end(), j - 1) - bef[in].second.begin();
                dp[i][j] = min(dp[i][j], dp[i][j - 1] + in - col1 - col2);
            }
        }
    }
    cout << dp[n][n] << endl;
    return 0;
}
