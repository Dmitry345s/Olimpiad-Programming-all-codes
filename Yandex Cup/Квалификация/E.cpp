#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

int fpow (int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (ans * a) % MOD;
        }
        x /= 2;
        a = (a * a) % MOD;
    }
    return ans;
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> op(n);
    vector<vector<int>> cl(n);
    vector<int> v(k);
    vector<int> difv(k);
    for (int i = 0; i < k; ++i) {
        int l, r, p, q;
        cin >> l >> r >> p >> q;
        --l; --r;
        op[l].push_back(i);
        cl[r].push_back(i);
        v[i] = p * fpow(q, MOD - 2) % MOD;
        difv[i] = (1 - v[i] + MOD) % MOD;
    }
    int ans = 0;
    int prdf = 1;
    vector<int> rans(n);
    for (int i = 0; i < n; ++i) {
        //cout << i << endl;
        for (int j : op[i]) {
            ans = (ans * difv[j]) % MOD;
            ans += v[j] * prdf;
            ans %= MOD;
            prdf *= difv[j];
            prdf %= MOD;
        }
        rans[i] = ans;
        for (int j : cl[i]) {
            prdf = (prdf * fpow(difv[j], MOD - 2)) % MOD;
            ans -= v[j] * prdf;
            ans = (ans % MOD + MOD) % MOD;
            ans = (ans * fpow(difv[j], MOD - 2)) % MOD;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << rans[i] << " ";
    }
    cout << endl;
}
