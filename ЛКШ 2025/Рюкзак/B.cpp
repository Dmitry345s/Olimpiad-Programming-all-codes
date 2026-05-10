#include<bits/stdc++.h>

using namespace std;

const int D = 1e4 + 1;

signed main() {
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    int in = -1;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        //cout << sum << " " << c << endl;
        if (sum + a[i] < c && in == i - 1) {
            sum += a[i];
            in = i;
        }
    }
    //cout << in << endl;
    if (in == n - 1) {
        cout << 0 << endl;
        return 0;
    }
    vector<vector<int>> dp(2 * D + 1, vector<int> (n + 1, -2));
    dp[sum - c + D][in + 1] = in + 1;
    //cout << sum - c + D << endl;
    //cout << in << endl;
    for (int i = in + 1; i < n; ++i) {
        for (int j = 0; j < 2 * D + 1; ++j) {
            dp[j][i + 1] = max(dp[j][i + 1], dp[j][i]);
            if (j + a[i] < 2 * D + 1) {
                dp[j + a[i]][i + 1] = max(dp[j + a[i]][i + 1], dp[j][i]);
            }
            int y = 1;
            if (i > 0) {
                y = max(y, dp[j][i - 1]);
            }
            for (int u = dp[j][i]; u >= y; --u) {
                int nsum = j + a[i] - a[u - 1];
                if (nsum >= 0 && nsum < 2 * D + 1) {
                    dp[nsum][i + 1] = max(dp[nsum][i + 1], u - 1);
                }
            }
        }
    }
    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * D + 1; ++j) {
            cout << dp[j][i] << " ";
        }
        cout << endl;
    }*/
    if (dp[D][n] == -2) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
    }
    return 0;
}
