#include<bits/stdc++.h>

#define int long long

using namespace std;

int mod = 998244353;
int ch;

int fast_pow(int a, int x) {
    int ans = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            ans *= a;
            ans %= mod;
        }
        a *= a;
        a %= mod;
        x /= 2;
    }
    return ans;
}

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> facts(n + q + 1);
    facts[0] = 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    if (q <= 100 && n <= 1e5) {
        for (int j = 0; j < q; ++j) {
            for (int i = 0; i < n; ++i) {
                if (i != 0) {
                    a[i] += a[i - 1];
                    a[i] %= mod;
                }
            }
        }
        for (int i = 0; i < n; ++i) {
            cout << a[i] << " ";
        }
        cout << endl;
        return 0;
    }
    vector<int> rev_facts(n + q + 1);
    rev_facts[0] = 1;
    for (int i = 1; i < n + q + 1; ++i) {
        facts[i] = facts[i - 1] * i;
        facts[i] %= mod;
        ch = i;
        rev_facts[i] = rev_facts[i - 1] * fast_pow(i, mod - 2);
        rev_facts[i] %= mod;
        //cout << facts[i] << " " << rev_facts[i] << endl;
    }
    vector<int> sufs(n + 1);
    sufs[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        sufs[i] = (sufs[i + 1] + a[i]) % mod;
    }
    vector<int> ans(n);
    for (int j = 0; j < n; ++j) {
        for (int i = j; i < n; ++i) {
            int d = (q - 1) + i - j;
            int u = i - j;
            //cout << u << " " << d << " " << facts[d] * rev_facts[u] * rev_facts[d - u] << endl;
            ans[i] += (a[j] * ((facts[d] * ((rev_facts[u] * rev_facts[d - u]) % mod)) % mod)) % mod;
            ans[i] %= mod;
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
