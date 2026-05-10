#include<bits/stdc++.h>

//# define int long long

using namespace std;

const int INF = 2e9;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> all(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> all[i][j];
        }
    }
    vector<vector<int>> prefs(n, vector<int> (n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            prefs[i][j + 1] = prefs[i][j] + all[i][j];
        }
    }
    vector<vector<int>> prec(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        prec[i][i] = 0;
        for (int j = i + 1; j < n; ++j) {
            prec[i][j] = prec[i][j - 1] + prefs[j][j + 1] - prefs[j][i];
        }
    }
    vector<vector<int>> dp(n, vector<int> (k + 1, INF));
    vector<vector<int>> opt(n + 1, vector<int> (k + 1, n));
    for (int i = 0; i < n; ++i) {
        dp[i][1] = prec[0][i];
        opt[i][1] = 0;
    }
    for (int tt = 2; tt <= k; ++tt) {
        for (int u = n - 1; u >= tt - 1; --u) {
            for (int c = opt[u][tt - 1]; c <= min(u - 1, opt[u + 1][tt]); ++c) {
                int now = dp[c][tt - 1] + prec[c + 1][u];
                if (dp[u][tt] > now) {
                    dp[u][tt] = now;
                    opt[u][tt] = c;
                }
            }
        }
    }
    cout << dp[n - 1][k] << endl;
    return 0;
}
