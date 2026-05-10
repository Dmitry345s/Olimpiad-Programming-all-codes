#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MOD = 998244353;

signed main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    vector<int> pref(n);
    vector<int> dp(n * m + 5);
    dp[0] = 1;
    vector<int> ch(n * m + 5);
    for (int i = 0; i < n; ++i) {
        int c = m - (s[i] - 'a') - 1;
        int del = 0;
        for (int j = 0; j <= m * (i + 1); ++j) {
            int x = dp[j];
            dp[j] = del;
            del += x;
            if (del >= MOD) del -= MOD;
            if (j + c < (int)ch.size()) {
                ch[j + c] -= x;
                if (ch[j + c] < 0) ch[j + c] += MOD;
            }
            del += ch[j];
            if (del >= MOD) del -= MOD;
            ch[j] = 0;
        }
        for (int j = 0; j <= n * m; j += i + 1) {
            pref[i] += dp[j];
            if (pref[i] >= MOD) pref[i] -= MOD;
        }
    }
    s.push_back('a');
    int now = 1;
    int ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        ans += ((pref[i] * (s[i + 1] - 'a' + 1)) % MOD * now) % MOD;
        ans %= MOD;
        if (i != n - 1) {
            now = (now * m) % MOD;
        }
    }
    cout << ans << endl;
    return 0;
}
