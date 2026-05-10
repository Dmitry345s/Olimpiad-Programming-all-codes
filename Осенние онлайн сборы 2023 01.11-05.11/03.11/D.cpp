#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> l[i] >> r[i];
        --l[i]; --r[i];
    }
    vector<int> pref(n);
    pref[0] = r[0];
    for (int i = 1; i < n; ++i) {
        pref[i] = max(pref[i - 1], r[i]);
    }
    /*if (n <= 300) {
        vector<vector<int>> dp(n, vector<int> (n, 1e9));
        dp[0][n - 1] = 0;
        for (int d = n - 1; d > 0; --d) {
            for (int nl = 0; nl < n - d + 1; ++nl) {
                int nr = nl + d - 1;
                for (int j = nl; j <= nr; ++j) {
                    int el1 = min(nl, l[j]), er1 = max(nr, r[j]);
                    dp[nl][nr] = min(dp[nl][nr], dp[el1][er1] + 1);
                }
            }
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int k;
            cin >> k;
            if (dp[k - 1][k - 1] == 1e9) {
                cout << -1 << endl;
            } else {
                cout << dp[k - 1][k - 1] << endl;
            }
        }
        return 0;
    }*/
    if (n <= 3000) {
        vector<vector<int>> dp(n, vector<int> (n, 1e9));
        dp[0][n - 1] = 0;
        for (int d = n - 1; d > 0; --d) {
            for (int nl = 0; nl < n - d + 1; ++nl) {
                int nr = nl + d - 1;
                int el1 = l[nl], er1 = max(nr, r[nl]);
                int el2 = min(nl, r[nr]), er2 = r[nr];
                dp[nl][nr] = min(dp[nl][nr], min(dp[el1][er1], dp[el2][er2]) + 1);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cout << dp[i][j] << " ";
            }
            cout << endl;
        }
        vector<vector<int>> dp2(n, vector<int> (n));
        for (int i = n - 1; i >= 0; --i) {
            for (int j = 0; j < n; ++j) {
                if (i == n - 1 && j == 0) {
                    dp2[i][j] = dp[i][j];
                    continue;
                }
                if (i == n - 1) {
                    dp2[i][j] = dp2[i][j - 1];
                    continue;
                }
                if (j == 0) {
                    dp2[i][j] = dp2[i + 1][j];
                    continue;
                }
                dp2[i][j] = min(dp2[i + 1][j], dp2[i][j - 1]);
            }
        }
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int k;
            cin >> k;
            if (dp2[k - 1][k - 1] == 1e9) {
                cout << -1 << endl;
            } else {
                cout << dp2[k - 1][k - 1] << endl;
            }
        }
        return 0;
    }
    int q;
    cin >> q;
    int k;
    cin >> k;
    if (q == 1 && k == 1) {
        int nr = 0;
        int ans = 0;
        while (nr != n - 1 && ans < 2 * n) {
            ans++;
            nr = pref[nr];
        }
        if (ans > n) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
        return 0;
    }
    return 0;
}
