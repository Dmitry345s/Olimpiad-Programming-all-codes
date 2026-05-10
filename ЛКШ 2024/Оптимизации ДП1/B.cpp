#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

void divide(int j, vector<vector<int>> & dp, vector<vector<int>> & pref, int l, int r, int cl, int cr) {
    if (l >= r) return;
    int m = (l + r) / 2;
    int opt = cl;
    //cout << m << " " << cl << " " << cr << " ";
    for (int i = cl; i < min(m, cr); ++i) {
        int cur = dp[i][j - 1] + pref[m][m] + pref[i][i] - pref[i][m] - pref[m][i];
        dp[m][j] = min(dp[m][j], cur);
        if (dp[m][j] == cur || dp[m][j] == INF) {
            opt = i;
        }
    }
    //cout << opt << endl;
    divide(j, dp, pref, l, m, cl, opt + 1);
    divide(j, dp, pref, m + 1, r, opt, cr);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> u(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> u[i][j];
        }
    }
    vector<vector<int>> pref(n + 1, vector<int> (n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + u[i - 1][j - 1];
        }
    }
    vector<vector<int>> dp(n + 1, vector<int> (k + 1, INF));
    dp[0][0] = 0;
    for (int i = 1; i <= k; ++i) {
        divide(i, dp, pref, 1, n + 1, 0, n + 1);
    }
    cout << dp[n][k] / 2 << endl;
    return 0;
}
