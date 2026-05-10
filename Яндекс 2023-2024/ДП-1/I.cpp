#include<bits/stdc++.h>

using namespace std;

int MAX = 101, C = 10, mod = 1e9 + 7;
vector<vector<int>> dp(MAX, vector<int> (C));

void start() {
    for (int i = 0; i < C; ++i) {
        dp[0][i] = 1;
    }
    for (int i = 1; i < MAX; ++i) {
        for (int j = 0; j < 10; ++j) {
            for (int l = j; l < C; ++l) {
                dp[i][j] += dp[i - 1][l];
                dp[i][j] %= mod;
            }
        }
    }
}

int get(string s) {
    int ans = 0;
    int n = s.size();
    for (int i = 0; i <= n; ++i) {
        if (i == n) {
            ans += 1;
            ans %= mod;
        }
        if (i >= 1 && s[i] < s[i - 1]) break;
        int fr = 0;
        if (i) {
            fr = s[i - 1] - '0';
        }
        for (int j = fr; j < s[i] - '0'; ++j) {
            ans += dp[n - i - 1][j];
            ans %= mod;
        }
    }
    return ans;
}

signed main() {
    start();
    string l, r;
    cin >> l >> r;
    int ch = 1;
    for (int i = 1; i < (int)l.size(); ++i) {
        if (l[i] < l[i - 1]) ch = 0;
    }
    cout << (get(r) - get(l) + ch + mod) % mod << endl;
    return 0;
}
