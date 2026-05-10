#include<bits/stdc++.h>

#define int long long

using namespace std;

int MOD = 1e9 + 7;
const int MAX = 351;

int fc[MAX], rfc[MAX];

int fpow(int a, int x) {
    int ans = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        x /= 2;
    }
    return ans;
}

int c(int k, int n) {
    return (((fc[n] * rfc[k]) % MOD) * rfc[n - k]) % MOD;
}

signed main() {
    int n;
    cin >> n;
    fc[0] = 1;
    rfc[0] = 1;
    //cout << fpow(2, 30) << endl;
    for (int i = 1; i <= n; ++i) {
        fc[i] = (fc[i - 1] * i) % MOD;
        rfc[i] = (rfc[i - 1] * fpow(i, MOD - 2)) % MOD;
        //cout << fc[i] << " " << rfc[i] << endl;
    }
    vector<vector<array<int, 2>>> dp(n + 1, vector<array<int, 2>> (n + 1, {0, 0}));
    for (int i = 0; i <= n; ++i) {
        if (i == 1) {
            dp[1][i][1] = c(i, n);
        } else {
            dp[1][i][0] = c(i, n);
        }
    }
    //cout << c(0, n) << endl;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            for (int k = 0; k < 2; ++k) {
                for (int x = 0; x <= n; ++x) {
                    if (x + j > n) continue;
                    if (x == i + 1) {
                        dp[i + 1][j + x][1] += (dp[i][j][k] * c(x, n - j)) % MOD;
                        if (dp[i + 1][j + x][1] >= MOD) dp[i + 1][j + x][1] -= MOD;
                    } else {
                        dp[i + 1][j + x][k] += (dp[i][j][k] * c(x, n - j)) % MOD;
                        if (dp[i + 1][j + x][k] >= MOD) dp[i + 1][j + x][k] -= MOD;
                    }
                }
            }
        }
    }
    //cout << dp[n - 1][n - 2][0] << " " << dp[n - 1][n - 2][1] << " " << dp[n - 1][n - 1][0] << " " << dp[n - 1][n - 1][1] << endl;
    cout << dp[n][n][1] << endl;
    return 0;
}
