#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<long long>> f(n + 1, vector<long long> (m + 1, 0));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            cin >> f[i][j];
        }
    }
    long long ans = 1e18;
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if ((i == 1 && j == 1) || (i == n && j == m)) {
                continue;
            }
            vector<vector<long long>> dp(n + 1, vector<long long> (m + 1, 0));
            dp[i][j] = -1e18;
            for (int l = 1; l < n + 1; ++l) {
                for (int k = 1; k < m + 1; ++k) {
                    if (l == i && k == j) {
                        continue;
                    }
                    if (dp[l - 1][k] != -1e18) {
                        dp[l][k] = dp[l - 1][k] + f[l][k];
                    }
                    if (dp[l][k - 1] != -1e18) {
                        dp[l][k] = max(dp[l][k], dp[l][k - 1] + f[l][k]);
                    }
                    if (!(l == 1 && k == 1) && dp[l][k] == f[l][k]) {
                        dp[l][k] = 0;
                    }
                }
            }
            if (dp[n][m] <= ans) {
                ans = dp[n][m];
            }
        }
    }
    cout << ans << endl;
    return 0;
}
