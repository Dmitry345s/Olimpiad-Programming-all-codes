#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<vector<int>> ln(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> ln[i][j];
        }
    }
    vector<vector<int>> dp((1 << n), vector<int> (n, 1e9)), p((1 << n), vector<int> (n, -1));
    dp[1][0] = 0;
    for (int i = 1; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1 == 0) continue;
            for (int k = 0; k < n; ++k) {
                if ((i >> k) & 1) continue;
                if (ln[j][k]) {
                    int mask = (i ^ (1 << k));
                    if (dp[mask][k] > dp[i][j] + ln[j][k]) {
                        dp[mask][k] = dp[i][j] + ln[j][k];
                        p[mask][k] = j;
                    }
                }
            }
        }
    }
    int ans = 1e9;
    int v = -1;
    for (int i = 0; i < n; ++i) {
        if (dp.back()[i] < ans) {
            ans = dp.back()[i];
            v = i;
        }
    }
    if (ans == 1e9) {
        cout << -1 << endl;
        return 0;
    }
    int mask = (1 << n) - 1;
    vector<int> rans;
    while (v != 0) {
        rans.push_back(v);
        int k = v;
        v = p[mask][v];
        mask -= (1 << k);
    }
    rans.push_back(0);
    reverse(rans.begin(), rans.end());
    cout << ans << endl;
    for (int i = 0; i < (int)rans.size(); ++i) {
        cout << rans[i] + 1 << " ";
    }
    return 0;
}
