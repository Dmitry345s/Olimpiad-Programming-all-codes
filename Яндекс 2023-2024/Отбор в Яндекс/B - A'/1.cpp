#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    int x = 0;
    for (int i = 0; i < n; ++i) {
        char p;
        cin >> p;
        a[n - i - 1] = p - '0';
        x += a[n - i - 1];
    }
    if (x == 0) {
        for (int i = 0; i < n; ++i) {
            cout << 1 << endl;
        }
        return 0;
    }
    int mod1 = x - 1, mod2 = x + 1;
    if (x <= 2) {
        mod1 = 2;
    }
    vector<int> pows1(n), pows2(n);
    pows1[0] = 1 % mod1;
    pows2[0] = 1 % mod2;
    for (int i = 1; i < n; ++i) {
        pows1[i] = (pows1[i - 1] << 1) % mod1;
        pows2[i] = (pows2[i - 1] << 1) % mod2;
    }
    int ch1 = 0, ch2 = 0;
    for (int i = 0; i < n; ++i) {
        ch1 += a[i] * pows1[i];
        ch2 += a[i] * pows2[i];
    }
    vector<int> dp(1e6);
    dp[0] = 0;
    for (int i = 1; i < dp.size(); ++i) {
        dp[i] = dp[i >> 1] + (i & 1);
    }
    for (int i = n - 1; i >= 0; --i) {
        int now;
        if (a[i] == 0) {
            now = ch2 + pows2[i];
            now %= mod2;
        } else {
            if (x == 1) {
                cout << 0 << endl;
                continue;
            }
            if (x == 2) {
                cout << 1 << endl;
                continue;
            }
            now = ch1 - pows1[i] + mod1;
            now %= mod1;
        }
        int ans = 1;
        while (now != 0) {
            now = now % dp[now];
            ans++;
        }
        cout << ans << endl;
    }
    return 0;
}
