#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, m;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    vector<vector<pair<int, int>>> dp(n + 1, vector<pair<int, int>> (m + 1, {1e9, 1e9}));
    dp[0][0] = {0, -1};
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            if (i == 0 && j == 0) {
                continue;
            }
            if (j != 0) {
                if (b[j - 1] == 0) {
                    int t = max(dp[i][j - 1].first + 2, dp[i][j - 1].second + 1);
                    if (max(t, dp[i][j - 1].second) < max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = {t, dp[i][j - 1].second};
                    } else if (max(t, dp[i][j - 1].second) == max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = min(dp[i][j], {t, dp[i][j - 1].second});
                    }
                } else {
                    int t = max(dp[i][j - 1].first + 1, dp[i][j - 1].second + 2);
                    if (max(t, dp[i][j - 1].first) < max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = {dp[i][j - 1].first, t};
                    } else if (max(t, dp[i][j - 1].first) == max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = min(dp[i][j], {dp[i][j - 1].first, t});
                    }
                }
            }
            if (i != 0) {
                if (a[i - 1] == 0) {
                    int t = max(dp[i - 1][j].first + 2, dp[i - 1][j].second + 1);
                    if (max(t, dp[i - 1][j].second) < max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = {t, dp[i - 1][j].second};
                    } else if (max(t, dp[i - 1][j].second) == max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = min(dp[i][j], {t, dp[i - 1][j].second});
                    }
                } else {
                    int t = max(dp[i - 1][j].first + 1, dp[i - 1][j].second + 2);
                    if (max(t, dp[i - 1][j].first) < max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = {dp[i - 1][j].first, t};
                    } else if (max(t, dp[i - 1][j].first) == max(dp[i][j].first, dp[i][j].second)) {
                        dp[i][j] = min(dp[i][j], {dp[i - 1][j].first, t});
                    }
                }
            }
        }
    }
    cout << max(dp[n][m].first, dp[n][m].second) << endl;
    return 0;
}
