#include<bits/stdc++.h>

using namespace std;

set<int> a;

void start() {
    for (int i = 1; i < 1000; ++i) {
        int ch = 0;
        for (int j = 1; j <= i; ++j) {
            if (i % j == 0) {
                ch++;
            }
        }
        if (ch == 2) {
            a.insert(i);
        }
    }
}

signed main() {
    int n;
    cin >> n;
    start();
    vector<vector<int>> dp(n + 1, vector<int> (100));
    for (auto val : a) {
        if (val >= 100) {
            dp[1][val % 100] += 1;
        }
    }
    int ans = 0;
    int mod = 1e9 + 9;
    for (int i = 2; i <= n - 2; ++i) {
        for (int j = 0; j < 100; ++j) {
            for (int k = 0; k < 10; ++k) {
                int u = j * 10 + k;
                if (u < 100) continue;
                if (a.find(u) != a.end()) {
                    dp[i][u % 100] += dp[i - 1][j];
                    dp[i][u % 100] %= mod;
                }
            }
        }
    }
    for (int i = 0; i < 100; ++i) {
        ans += dp[n - 2][i];
        ans %= mod;
    }
    cout << ans << endl;
    return 0;
}
