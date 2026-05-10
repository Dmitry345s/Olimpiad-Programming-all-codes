#include<bits/stdc++.h>

using namespace std;

const int MAX = 4e3 + 2, INF = 2e9;
int pref[MAX][MAX];

void solve(int l, int r, int c, int optl, int optr, vector<vector<int>> & dp) {
    if (l == r) return;
    //cout << l << " " << r << endl;
    int m = (l + r) / 2;
    //cout << m << endl;
    int last = -1;
    for (int i = optl; i <= min(m, optr) ; ++i) {
        int x = 0;
        if (i >= 1) x = dp[i - 1][c - 1];
        int now = x + (pref[m + 1][m + 1] + pref[i][i] - pref[m + 1][i] - pref[i][m + 1]);
        //cout << dp[i][c - 1] << endl;
        //cout << i << " " << now << endl;
        if (now < dp[m][c]) {
            dp[m][c] = now;
            last = i;
        }
    }
    //cout << dp[m][c] << " " << last << endl;
    solve(l, m, c, optl, last + 1, dp);
    solve(m + 1, r, c, last, optr, dp);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    //cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<vector<int>> a(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + a[i - 1][j - 1];
        }
    }
    vector<vector<int>> dp(n, vector<int> (k, INF)), opt(n, vector<int> (k));
    for (int i = 0; i < n; ++i) {
        dp[i][0] = pref[i + 1][i + 1];
        opt[i][0] = 0;
    }
    for (int i = 1; i < k; ++i) {
        //cout << i << endl;
        solve(0, n, i, 0, n, dp);
    }
    cout << dp[n - 1][k - 1] / 2 << endl;
    return 0;
}
