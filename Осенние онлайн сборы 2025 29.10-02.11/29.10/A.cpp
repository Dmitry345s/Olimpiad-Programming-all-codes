#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 2e5 + 1, MOD = 1e9 + 7;

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        x /= 2;
    }
    return ans;
}

int f[MAX], rf[MAX];

int c(int k, int n) {
    if (k > n) return 0;
    return f[n] * rf[n - k] % MOD * rf[k] % MOD;
}

int get0(int n, int k) {
    return c(k - 1, n + k - 1);
}

int get1(int n, int k) {
    return c(k - 1, n - 1);
}

signed main() {
    f[0] = 1;
    rf[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        f[i] = (f[i - 1] * i) % MOD;
        rf[i] = (rf[i - 1] * fpow(i, MOD - 2)) % MOD;
    }
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << get1(a[0], k) << endl;
        return 0;
    }
    if (n == 2) {
        int ans = 0;
        for (int p = 0; p < k; ++p) {
            ans += (c(p, k) * get1(a[0], k - p)) % MOD * get0(a[1] - p, k);
            ans %= MOD;
        }
        cout << ans << endl;
        return 0;
    }
    vector<int> cnt(k);
    for (int i = 0; i < k; ++i) {
        int y = c(i, k);
        for (int j = 0; j < n; ++j) {
            y *= get0(a[j], k - i);
            y %= MOD;
        }
        cnt[i] = y;
    }
    cout << endl;
    for (int i = k - 2; i >= 0; --i) {
        for (int j = i + 1; j < k; ++j) {
            cnt[i] -= (cnt[j] * c(i, j)) % MOD;
            cnt[i] = (cnt[i] + MOD) % MOD;
        }
    }
    cout << cnt[0] << endl;
    return 0;
}
