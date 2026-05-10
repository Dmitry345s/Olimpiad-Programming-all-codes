#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    vector<vector<vector<int>>> dp(n, vector<vector<int>> (m, vector<int> (1 << 14)));
    dp[0][0][0] = a[0][0];
    vector<vector<int>> b(n, vector<int> (m));
    vector<pair<int, int>> mp = {{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    for (int _ = 1; _ < k; ++_) {
        //cout << _ << endl;
        vector<vector<vector<int>>> ndp(n, vector<vector<int>> (m, vector<int> (1 << 14)));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                //cout << i << " " << j << endl;
                for (int c = 0; c < (1 << 14); ++c) {
                    ////cout << i << " " << j << " " << c << endl;
                    if (dp[i][j][c] == 0) continue;
                    if (i + 1 < n) {
                        b[i + 1][j] = a[i + 1][j];
                    }
                    if (j + 1 < m) {
                        b[i][j + 1] = a[i][j + 1];
                    }
                    if (i - 1 >= 0) {
                        b[i - 1][j] = a[i - 1][j];
                    }
                    if (j - 1 >= 0) {
                        b[i][j - 1] = a[i][j - 1];
                    }
                    int x = i, y = j;
                    for (int to_get = 6; to_get >= 0; --to_get) {
                        int nnew = (c >> (2 * to_get)) % 4;
                        x += mp[nnew].first;
                        y += mp[nnew].second;
                        if (x < 0) break;
                        //if (y < 0) break;
                        //if (x >= n) break;
                        //if (y >= m) break;
                        b[x][y] = min(b[x][y], (1 << (6 - to_get)));
                    }
                    int c2 = (c >> 2);
                    if (i + 1 < n) {
                        if (b[i + 1][j] >= a[i + 1][j]) {
                            ndp[i + 1][j][c2 + (0 << 12)] = max(ndp[i + 1][j][c2 + (0 << 12)], dp[i][j][c] + a[i + 1][j]);
                        }
                    }
                    if (j + 1 < m) {
                        if (b[i][j + 1] >= a[i][j + 1]) {
                            ndp[i][j + 1][c2 + (1 << 12)] = max(ndp[i][j + 1][c2 + (1 << 12)], dp[i][j][c] + a[i][j + 1]);
                        }
                    }
                    if (i - 1 >= 0) {
                        if (b[i - 1][j] >= a[i - 1][j]) {
                            ndp[i - 1][j][c2 + (2 << 12)] = max(ndp[i - 1][j][c2 + (2 << 12)], dp[i][j][c] + a[i - 1][j]);
                        }
                    }
                    if (j - 1 >= 0) {
                        if (b[i][j - 1] >= a[i][j - 1]) {
                            ndp[i][j - 1][c2 + (3 << 12)] = max(ndp[i][j - 1][c2 + (3 << 12)], dp[i][j][c] + a[i][j - 1]);
                        }
                    }
                }
            }
        }
        dp = ndp;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int c = 0; c < (1 << 14); ++c) {
                ans = max(ans, dp[i][j][c]);
            }
            //cout << i << " " << j << " " << ans << endl;
        }
    }
    cout << ans << endl;
    return 0;
}
