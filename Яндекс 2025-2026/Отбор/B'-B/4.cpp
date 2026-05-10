#include<bits/stdc++.h>

using namespace std;

const int MAX = 301;
int dp[MAX][MAX][MAX];

signed main() {
    int n, a, b;
    cin >> n >> a >> b;
    vector<int> c(n), t(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i] >> t[i];
    }
    for (int i = 0; i <= n; ++i) {
        for (int j = 0; j <= a; ++j) {
            for (int k = 0; k <= b; ++k) {
                dp[i][j][k] = MAX;
            }
        }
    }
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        for (int x = 0; x <= a; ++x) {
            for (int y = 0; y <= b; ++y) {
                if (dp[i - 1][x][y] != MAX) {
                    dp[i][x][y] = min(dp[i][x][y], dp[i - 1][x][y]);
                    dp[i][min(x + c[i - 1], a)][min(y + t[i - 1], b)] = min(dp[i][min(x + c[i - 1], a)][min(y + t[i - 1], b)], dp[i - 1][x][y] + 1);
                }
            }
        }
    }
    if (dp[n][a][b] == MAX) {
        cout << -1 << endl;
        return 0;
    }
    cout << dp[n][a][b] << endl;
    return 0;
}
