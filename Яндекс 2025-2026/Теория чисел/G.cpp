#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7, MAX = 2e6 + 1;
int fc[MAX], rfc[MAX];
int cnt[MAX], cnt2[MAX], sieve[MAX];

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (1ll * ans * a) % MOD;
        }
        a = (1ll * a * a) % MOD;
        x /= 2;
    }
    return ans;
}

int c(int k, int n) {
    return 1ll * fc[n] * rfc[k] % MOD * 1ll * rfc[n - k] % MOD;
}

signed main() {
    int n, k;
    cin >> n >> k;
    int ps = 0;
    for (int i = 2; i <= n; ++i) {
        if (sieve[i] == 0) {
            ps++;
            for (int j = i; j <= n; j += i) {
                sieve[j] = i;
            }
        }
    }
    cnt[1] = 0;
    for (int i = 2; i <= n; ++i) {
        cnt[i] = cnt[i / sieve[i]] + 1;
    }
    for (int i = 2; i <= n; ++i) {
        int u = sieve[i];
        int x = i;
        while (x % u == 0) {
            x /= u;
        }
        cnt2[i] = cnt2[x] + 1;
    }
    fc[0] = 1;
    rfc[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        fc[i] = (1ll * fc[i - 1] * i) % MOD;
        rfc[i] = (1ll * rfc[i - 1] * fpow(i, MOD - 2)) % MOD;
    }
    vector<int> ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            int tt = cnt2[j / i];
            if (cnt[j / i] > k) continue;
            ans[j] += c(ps - tt, k - cnt[j / i] + ps - tt);
            if (ans[j] >= MOD) ans[j] -= MOD;
        }
    }
    long long rans = 0;
    for (int i = 1; i <= n; ++i) {
        rans += 1ll * ans[i] * i;
        rans %= MOD;
    }
    cout << rans << endl;
    return 0;
}
