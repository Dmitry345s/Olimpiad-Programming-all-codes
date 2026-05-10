#include<bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

int fpow(int a, int x) {
    int ans = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            ans = (1ll * ans * a) % MOD;
        }
        a = (1ll * a * a) % MOD;
        x /= 2;
    }
    return ans;
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> sieve(n + 1);
    int cnt = 0;
    for (int i = 2; i <= n; ++i) {
        if (sieve[i] != 0) continue;
        cnt++;
        for (int j = i; j <= n; j += i) {
            if (sieve[j] == 0) {
                sieve[j] = i;
            }
        }
    }
    vector<int> cnt1(n + 1), cnt2(n + 1);
    for (int i = 2; i <= n; ++i) {
        int j = i / sieve[i];
        cnt2[i] = cnt2[j];
        cnt1[i] = cnt1[j] + 1;
        if (sieve[j] != sieve[i]) {
            cnt2[i]++;
        }
    }
    vector<int> fact(1e6 + 1e5 + 1);
    vector<int> revfact(1e6 + 1e5 + 1);
    fact[0] = 1;
    revfact[0] = 1;
    for (int i = 1; i <= 1e6 + 1e5; ++i) {
        fact[i] = (1ll * fact[i - 1] * i) % MOD;
        revfact[i] = fpow(fact[i], MOD - 2);
    }
    int ans = 0;
    vector<int> to_ans(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; j += i) {
            int alp = k - cnt1[i];
            if (alp < 0) continue;
            int ost = cnt - cnt2[i];
            int coun = (1ll * ((1ll * fact[alp + ost] * revfact[ost]) % MOD) * revfact[alp]) % MOD;
            //cout << coun << endl;
            to_ans[j] = (to_ans[j] + coun);
            if (to_ans[j] >= MOD) to_ans[j] -= MOD;
        }
    }
    for (int i = 1; i <= n; ++i) {
        ans = (ans + (1ll * i * to_ans[i]) % MOD) % MOD;
    }
    cout << ans << endl;
    return 0;
}
