#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<int> g(MAX), c(MAX);
vector<array<int, 2>> tr(MAX);
vector<array<int, 2>> dp(MAX, {(int)1e9, (int)1e9});

void dfs(int v, int n) {
    if ((n - 1) / 2 <= v) return;
    dfs(2 * v + 1, n);
    dfs(2 * v + 2, n);
    for (int i = 0; i < 4; ++i) {
        if (!tr[2 * v + 1][i & 1] || !tr[2 * v + 2][(i >> 1)]) continue;
        //cout << i << endl;
        int g1 = g[v], g2 = (g[v] ^ c[v]);
        //cout << g1 << " " << g2 << endl;
        int k = (i >> 1);
        if (g1) {
            k &= (i & 1);
        } else {
            k |= (i & 1);
        }
        tr[v][k] |= 1;
        dp[v][k] = min(dp[v][k], dp[2 * v + 1][i & 1] + dp[2 * v + 2][i >> 1]);
        int k2 = (i >> 1);
        if (g2) {
            k2 &= (i & 1);
        } else {
            k2 |= (i & 1);
        }
        //cout << k << " " << k2 << endl;
        dp[v][k2] = min(dp[v][k2], dp[2 * v + 1][i & 1] + dp[2 * v + 2][i >> 1] + 1);
        tr[v][k2] |= 1;
    }
}

signed main() {
    int n, v;
    cin >> n >> v;
    for (int i = 0; i < (n - 1) / 2; ++i) {
        cin >> g[i] >> c[i];
    }
    for (int i = (n - 1) / 2; i < n; ++i) {
        int ch;
        cin >> ch;
        tr[i][ch] = 1;
        dp[i][ch] = 0;
    }
    dfs(0, n);
    if (dp[0][v] == (int)1e9) {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }
    cout << dp[0][v] << endl;
    return 0;
}
