#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

signed main() {
    int n, k, m;
    cin >> n >> m >> k;
    vector<int> now(n, k);
    vector<vector<int>> tr(n);
    vector<int> mx(m);
    for (int i = 0; i < m; ++i) {
        //cout << i << endl;
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        mx[i] = x;
        for (int u = l; u < r; ++u) {
            now[u] = min(now[u], x);
            tr[u].push_back(i);
        }
    }
    //cout << -1 << endl;
    vector<vector<int>> dp(n + 1, vector<int> (1 << m));
    dp[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < (1 << m); ++j) {
            for (int u = 1; u <= now[i]; ++u) {
                int nmask = j;
                for (auto in : tr[i]) {
                    if (mx[in] == u) {
                        nmask |= (1 << in);
                    }
                }
                dp[i + 1][nmask] = (dp[i + 1][nmask] + dp[i][j]) % MOD;
            }
        }
    }
    cout << dp[n][(1 << m) - 1] << endl;
    return 0;
}
