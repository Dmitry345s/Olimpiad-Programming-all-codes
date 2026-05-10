#include<bits/stdc++.h>

#define int long long
#define double long double

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }
    /*vector<vector<vector<array<double, 3>>>> dp(n, vector<vector<array<double, 3>>> (k + 1, vector<array<double, 3>> (m + 1, {0, 0, 0})));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= k; ++j) {
            //dp[i][j][0] = {1e9, 0, 0};
        }
    }
    dp[0][0][1] = {a[0], a[0], 1};
    dp[0][0][0] = {1e9, 0, 0};
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < k; ++j) {
            for (int l = 0; l <= m; ++l) {
                if (l > i + 1) continue;
                if (l != m && j == 0 && l != i + 1) continue;
                if (l != m && j * m + l > i + 1) continue;
                if (l < m) {
                    dp[i + 1][j][l + 1] = {min(dp[i - l + 1][j][0][0], (double)(dp[i][j][l][1] + a[i + 1]) / (double)(l + 1)), dp[i][j][l][1] + a[i + 1], l + 1};
                } else {
                    if (dp[i][j + 1][0][0] < dp[i][j][l][0]) {
                        dp[i][j + 1][0] = dp[i][j][l];
                    } else if (dp[i][j + 1][m][0] == dp[i][j][l][0] && dp[i][j + 1][l][1] / dp[i][j + 1][l][2]  > dp[i + 1][j + 1][1][1] / dp[i + 1][j + 1][1][2]) {
                        dp[i][j + 1][0] = dp[i][j][l];
                    }
                    double now = (dp[i][j][l][1] + a[i + 1]) / (double)(dp[i][j][l][2] + 1);
                    if (dp[i + 1][j][m][0] < min(dp[i][j][l][0], now)) {
                        dp[i + 1][j][m] = {min(dp[i][j][l][0], now), (dp[i][j][l][1] + a[i + 1]), dp[i][j][l][2] + 1};
                    } else if (dp[i + 1][j][m][0] == min(dp[i][j][l][0], now) && now > dp[i + 1][j][m][1] / dp[i + 1][j][m][2]) {
                        dp[i + 1][j][m] = {min(dp[i][j][l][0], now), (dp[i][j][l][1] + a[i + 1]), dp[i][j][l][2] + 1};
                    }
                }
                cout << i << " " << j << " " << l << " " << dp[i][j][l][0] << endl;
            }
        }
    }
    cout << dp[n - 1][k][m][0] << endl;*/
    vector<vector<array<double, 3>>> dp(n, vector<array<double, 3>> (k + 1));
    vector<vector<int>> p(n, vector<int> (k + 1));
    for (int i = m - 1; i < n; ++i) {
        dp[i][1] = {pref[i + 1] / (double)(i + 1), pref[i + 1], i + 1};
        p[i][1] = i + 1;
    }
    for (int i = 1; i < n; ++i) {
        for (int j = 2; j <= k; ++j) {
            if (j * m > i + 1) continue;
            if (dp[i - 1][j][2] != 0) {
                int l = i - 1 - dp[i - 1][j][2];
                if (dp[i][j][0] < min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l))) {
                    dp[i][j] = {min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)), (pref[i + 1] - pref[l + 1]), (i - l)};
                    p[i][j] = i - l;
                } else if (dp[i][j][0] == min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)) && dp[i][j][1] / dp[i][j][2] < (pref[i + 1] - pref[l + 1]) / (double)(i - l)){
                    dp[i][j] = {min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)), (pref[i + 1] - pref[l + 1]), (i - l)};
                    p[i][j] = i - l;
                } else if (dp[i][j][0] == min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)) && dp[i][j][1] / dp[i][j][2] == (pref[i + 1] - pref[l + 1]) / (double)(i - l)) {
                    if (dp[i][j][2] > i - l) {
                        dp[i][j] = {min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)), (pref[i + 1] - pref[l + 1]), (i - l)};
                        p[i][j] = i - l;
                    }
                }
            }
            int l = i - m;
            if (dp[i][j][0] < min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l))) {
                dp[i][j] = {min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)), (pref[i + 1] - pref[l + 1]), (i - l)};
                p[i][j] = i - l;
            } else if (dp[i][j][0] == min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)) && dp[i][j][1] / dp[i][j][2] < (pref[i + 1] - pref[l + 1]) / (double)(i - l)){
                dp[i][j] = {min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)), (pref[i + 1] - pref[l + 1]), (i - l)};
                p[i][j] = i - l;
            } else if (dp[i][j][0] == min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)) && dp[i][j][1] / dp[i][j][2] == (pref[i + 1] - pref[l + 1]) / (double)(i - l)) {
                if (dp[i][j][2] > i - l) {
                    dp[i][j] = {min(dp[l][j - 1][0], (pref[i + 1] - pref[l + 1]) / (double)(i - l)), (pref[i + 1] - pref[l + 1]), (i - l)};
                    p[i][j] = i - l;
                }
            }
            //cout << i << " " << j << " " << dp[i][j][0] << endl;
        }
    }
    vector<int> ans;
    int now = n - 1, now2 = k;
    while (now2 > 0) {
        ans.push_back(p[now][now2]);
        now -= p[now][now2];
        now2--;
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < k; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
