#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 998244353;

signed main() {
    int n;
    cin >> n;
    if (n == 1) {
        cout << 1 << endl;
        return 0;
    }
    if (n < 3) {
        cout << 0 << endl;
        return 0;
    }
    /*vector<int> dp(n + 1);
    vector<int> odp(n + 1);
    dp[1] = 1;
    odp[1] = 0;
    dp[2] = 0;
    odp[2] = 2;
    for (int i = 3; i <= n; ++i) {
        dp[i] = dp[i - 1] * (i - 2);
        dp[i] %= MOD;
        for (int j = 1; j < i - 1; ++j) {
            dp[i] = (dp[i] + odp[j]) % MOD;
        }
        odp[i] = dp[i - 1] * 2 + odp[i - 1];
        odp[i] %= MOD;
        odp[i - 1] = odp[i - 1] * (i - 2);
        odp[i - 1] %= MOD;
        for (int j = i - 2; j >= 2; --j) {
            odp[j] = (odp[j] * (i - 3)) % MOD;
        }
        cout << odp[1] << " " << odp[2] << " " << odp[3] << " " << odp[4] << endl;
    }
    cout << odp[n] << " " << dp[n] << endl;*/
    vector<vector<int>> g(n, vector<int> (n, 1));
    for (int i = 0; i < n - 1; ++i) {
        int s, f;
        cin >> s >> f;
        --s; --f;
        g[s][f] = 0;
        g[f][s] = 0;
    }
    vector<vector<int>> dp((1 << n), vector<int> (n));
    for (int i = 0; i < n; ++i) {
        dp[(1 << i)][i] = 1;
    }
    for (int mask = 1; mask < (1 << n); ++mask) {
        for (int v = 0; v < n; ++v) {
            if (!((mask >> v) & 1)) continue;
            for (int j = 0; j < n; ++j) {
                if ((mask >> j) & 1) continue;
                if (g[v][j]) {
                    dp[mask + (1 << j)][j] += dp[mask][v];
                    dp[mask + (1 << j)][j] %= MOD;
                }
            }
        }
    }
    int ans = 0;
    for (int v = 0; v < n; ++v) {
        ans = (ans + dp.back()[v]) % MOD;
    }
    cout << ans << endl;
    //assert(n != 6 || ans == 480);
    return 0;
}

/*
1 2
2 3
3 4
4 5
5 6
6 7
7 8
8 9
9 10
10 11
11 12
12 13
13 14
14 15
15 16
16 17
17 18
18 19
19 20
*/
