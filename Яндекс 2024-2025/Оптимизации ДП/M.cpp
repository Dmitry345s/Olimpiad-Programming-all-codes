#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 2e4 + 5, INF = 1e18;
int w[MAX], d[MAX];
int pref1[MAX], pref2[MAX], pref3[MAX];

void solve(int l, int r, int c, int optl, int optr, vector<vector<int>> & dp) {
    if (l == r) return;
    int m = (l + r) / 2;
    int last = -1;
    for (int i = min(m, optr - 1); i >= optl; --i) {
        int x = 0;
        if (i != 0) {
            x = dp[i - 1][c - 1];
        }
        int cnt = (pref3[i] - pref3[m + 1]) - (pref1[m] * (pref2[m + 1] - pref2[i]));
        int now = x + cnt;
        if (now < dp[m][c]) {
            dp[m][c] = now;
            last = i;
        }
        //cout << m << " " << i << " " << len << " " << cnt << endl;
        if (i == 0) continue;
    }
    //cout << "! " << m << " " << dp[m][c] << endl;
    solve(l, m, c, optl, last + 1, dp);
    solve(m + 1, r, c, last, optr, dp);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> d[i];
    }
    for (int i = n - 1; i >= 0; --i) {
        pref1[i] = pref1[i + 1] + d[i];
        pref3[i] = pref3[i + 1] + pref1[i] * w[i];
    }
    for (int i = 0; i < n; ++i) {
        pref2[i + 1] = pref2[i] + w[i];
    }
    vector<vector<int>> dp(n + 1, vector<int> (4, INF));
    for (int i = 1; i < 4; ++i) {
        //cout << "#" << endl;
        solve(0, n + 1, i, 0, n + 1, dp);
    }
    cout << dp[n][3] << endl;
    return 0;
}
