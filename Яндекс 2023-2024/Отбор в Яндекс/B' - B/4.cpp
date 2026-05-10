#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        char p;
        cin >> p;
        if (p == 'M') {
            a[i] = 0;
        }
        if (p == 'P') {
            a[i] = 1;
        }
        if (p == 'G') {
            a[i] = 2;
        }
    }
    vector<vector<vector<int>>> dp(n, vector<vector<int>> (k + 1, vector<int> (3)));
    dp[0][0][a[0]] = 1;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            for (int l = 0; l < 3; ++l) {
                dp[i][j][l] = dp[i - 1][j][l];
                if (j != 0) {
                    for (int p = 0; p < 3; ++p) {
                        dp[i][j][l] = max(dp[i][j][l], dp[i - 1][j - 1][p]);
                    }
                }
                dp[i][j][l] += (a[i] == l);
            }
        }
    }
    cout << max(dp[n - 1][k][0], max(dp[n - 1][k][1], dp[n - 1][k][2])) << endl;
    return 0;
}
