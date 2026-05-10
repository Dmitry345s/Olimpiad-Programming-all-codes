#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> f(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    vector<vector<int>> dp(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == 0 && j == 0) {
                dp[i][j] = f[i][j];
                continue;
            }
            if (i == 0) {
                dp[i][j] = dp[i][j - 1] + f[i][j];
                continue;
            }
            if (j == 0) {
                dp[i][j] = dp[i - 1][j] + f[i][j];
                continue;
            }
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]) + f[i][j];
        }
    }
    vector<vector<int>> dp2(n, vector<int> (m));
    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (i == n - 1 && j == m - 1) {
                dp2[i][j] = f[i][j];
                continue;
            }
            if (i == n - 1) {
                dp2[i][j] = dp2[i][j + 1] + f[i][j];
                continue;
            }
            if (j == m - 1) {
                dp2[i][j] = dp2[i + 1][j] + f[i][j];
                continue;
            }
            dp2[i][j] = max(dp2[i + 1][j], dp2[i][j + 1]) + f[i][j];
        }
    }
    long long ans = 1e18;
    for (int i = 1; i < n; ++i) {
        vector<int> a;
        int j = 0;
        int i2 = i;
        while (j < m && i2 >= 0) {
            a.push_back(dp[i2][j] + dp2[i2][j] - f[i2][j]);
            j++;
            i2--;
        }
        sort(a.rbegin(), a.rend());
        ans = min(ans, a[1]);
    }
    for (int j = 1; j < m - 1; ++j) {
        vector<int> a;
        int i = n - 1;
        int j2 = j;
        while (j2 < m && i >= 0) {
            a.push_back(dp[i][j2] + dp2[i][j2] - f[i][j2]);
            j2++;
            i--;
        }
        sort(a.rbegin(), a.rend());
        ans = min(ans, a[1]);
    }
    cout << ans << endl;
    return 0;
}
