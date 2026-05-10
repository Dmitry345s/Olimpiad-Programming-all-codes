#include<bits/stdc++.h>

#define int long long

using namespace std;

int fpow(int a, int x, int m) {
    int ans = 1;
    while (x > 0) {
        if (x % 2) {
            ans = (ans * a) % m;
        }
        a = (a * a) % m;
        x /= 2;
    }
    return ans;
}

signed main() {
    int n, m;
    cin >> n >> m;
    int nfc = 1;
    if (n < m) {
        for (int i = 1; i <= n; ++i) {
            nfc *= i;
            nfc %= m;
        }
    } else {
        nfc = 0;
    }
    vector<int> dp(m + 2);
    dp[1] = 1;
    dp[2] = 1;
    for (int i = 3; i <= m + 1; ++i) {
        dp[i] = (i - 1) * dp[i - 1] + (i - 2) * dp[i - 2];
        dp[i] %= m;
    }
    if (n < m) {
        cout << (nfc - dp[n] + m) % m << endl;
        return 0;
    }
    //cout << dp[m - 1] << endl;
    //cout << dp[m + 1] << endl;
    if (n % m == 0) {
        cout << (m - ((fpow(m - dp[m - 1], n / m, m) * dp[m]) % m)) % m << endl;
        return 0;
    }
    cout << (m - ((fpow(m - dp[m - 1], n / m, m) * dp[n % m]) % m)) % m << endl;
    return 0;
}
