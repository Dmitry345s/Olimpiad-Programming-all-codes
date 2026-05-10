#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7, MAX = 1e5 + 5;

int fpow(int a, int x) {
    int ans = 1;
    while(x) {
        if (x % 2) {
            ans = (ans * a) % MOD;
        }
        x /= 2;
        a = (a * a) % MOD;
    }
    return ans;
}

int rf[MAX], f[MAX];

int c(int k, int n) {
    return f[n] * rf[n - k] % MOD * rf[k] % MOD;
}

signed main() {
    int n, k;
    cin >> n >> k;
    f[0] = 1;
    rf[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        f[i] = (f[i - 1] * i) % MOD;
        rf[i] = (rf[i - 1] * fpow(i, MOD - 2)) % MOD;
    }
    int ans = 0;
    int pr = 0;
    int cnt = 0;
    for (int j = 0; j <= k; ++j) {
        int cn = c(j, k);
        pr = (pr + cn) % MOD;
        int u = (fpow(pr, n - 1) - cnt + MOD) % MOD;
        ans = (ans + u * j) % MOD;
        cnt = (cnt + u) % MOD;
    }
    ans = (ans * fpow(2, k)) % MOD;
    ans = (ans * fpow(fpow(2, n * k), MOD - 2)) % MOD;
    cout << ans << endl;
    return 0;
}
