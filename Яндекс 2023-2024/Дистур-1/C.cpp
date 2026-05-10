#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

//#define int long long

using namespace std;

signed main() {
    long long mod = 1e9 + 7;
    int n, x, k;
    cin >> n >> x >> k;
    vector<vector<vector<vector<int>>>> dp(2, vector<vector<vector<int>>> (x + 1, vector<vector<int>> (k + 1, vector<int> (3))));
    vector<vector<vector<int>>> ch(x + 1, vector<vector<int>> (k + 1, vector<int> (3)));
    vector<long long> last(k + 1);
    for (int i = 1; i < n + 1; ++i) {
        dp[i & 1] = ch;
        long long ans = 0;
        long long ans3 = 0;
        for (int l = 0; l < k + 1; ++l) {
            ans = 0;
            ans3 = 0;
            long long ans2 = 0;
            for (int j = x; j >= 1; --j) {
                if (i == 1) {
                    if (l == 0) {
                        dp[i & 1][j][l][2] = 1;
                        ans2 += 1;
                    }
                    continue;
                }
                if (l < k) {
                    dp[i & 1][j][l + 1][1] += (ans % mod);
                    dp[i & 1][j][l + 1][1] %= mod;
                }
                dp[i & 1][j][l][1] += (ans3 % mod);
                dp[i & 1][j][l][1] %= mod;
                dp[i & 1][j][l][2] = (dp[(i + 1) % 2][j][l][0] + (long long)dp[(i + 1) & 1][j][l][1] + dp[(i + 1) & 1][j][l][2]) % mod;
                ans += dp[(i + 1) & 1][j][l][0];
                ans3 += (dp[(i + 1) & 1][j][l][1] + (long long)dp[(i + 1) & 1][j][l][2]);
                dp[i & 1][j][l][0] += (last[l] - ans - ans3) % mod;
                dp[i & 1][j][l][0] %= mod;
                ans2 += dp[i & 1][j][l][0] + dp[i & 1][j][l][1] + dp[i & 1][j][l][2];
            }
            last[l] = ans2;
        }
    }
    long long rans = 0;
    for (int j = 0; j <= x; ++j) {
        rans += dp[n % 2][j][k][0] + (long long)dp[n % 2][j][k][1] + dp[n % 2][j][k][2];
        rans %= mod;
    }
    cout << rans << '\n';
    return 0;
}
