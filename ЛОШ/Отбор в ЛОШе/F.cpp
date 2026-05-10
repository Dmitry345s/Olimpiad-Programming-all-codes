#include<iostream>
#include<vector>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int> (m + 1));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            char p;
            cin >> p;
            a[i][j] = p - '0';
        }
    }
    vector<vector<pair<long long, long long>>> dp(n + 1, vector<pair<long long, long long>> (m + 1, {0, 0}));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (i == 1 && j == 1) {
                if (a[i][j] == 0) {
                    dp[i][j].first = 1;
                } else {
                    dp[i][j].second = 1;
                }
                continue;
            }
            if (a[i][j] == 1) {
                dp[i][j].second = dp[i - 1][j].first + dp[i - 1][j].second + dp[i][j - 1].second + dp[i][j - 1].first;
            } else {
                dp[i][j].second = dp[i - 1][j].second + dp[i][j - 1].second;
                dp[i][j].first = dp[i - 1][j].first + dp[i][j - 1].first;
            }
        }
    }
    cout << dp[n][m].second << endl;
    return 0;
}
