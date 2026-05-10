#include<bits/stdc++.h>

using namespace std;

const int MAX = 501, MASK = (1 << 15);
int dp[MAX][MASK][2];

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
    }
    dp[0][0][1] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < MASK; ++j) {
            vector<int> all;
            int x = 0;
            int x2 = 0;
            for (int k = 0; k < 15; ++k) {
                if ((j >> k) & 1) {
                    if (k <= a[i]) {
                        x++;
                        x2 = k;
                    }
                }
            }
            if (x == 0) {
                dp[i + 1][j][0] |= dp[i][j][1];
                int j2 = (1 << a[i]) + j;
                dp[i + 1][j2][1] |= (dp[i][j][0] | dp[i][j][1]);
            } else {
                int j2 = j;
                j2 ^= (1 << x2);
                j2 ^= (1 << a[i]);
                dp[i + 1][j2][1] |= (dp[i][j][0] | dp[i][j][1]);
                dp[i + 1][j][0] |= (dp[i][j][1]);
            }
        }
    }
    int ans = 15;
    for (int j = 0; j < MASK; ++j) {
        vector<int> all;
        for (int k = 0; k < 15; ++k) {
            if ((j >> k) & 1) {
                all.push_back(k);
            }
        }
        if (dp[n][j][0] || dp[n][j][1]) {
            ans = min(ans, (int)all.size());
        }
    }
    cout << ans << endl;
    return 0;
}
