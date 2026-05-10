#include<bits/stdc++.h>

#define int __int128

using namespace std;
using ll = long long;

const int MOD = 1000000000000000000 + 31, G = 42, MAX = 1e6 + 1;
ll ans[MAX];

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = ((__int128)ans * a) % MOD;
        }
        a = ((__int128)a * a) % MOD;
        x /= 2;
    }
    return ans;
}

signed main() {
    ll n;
    cin >> n;
    ans[MAX - 1] = 300;
    for (int i = MAX - 2; i >= 0; --i) {
        ans[i] = fpow(42, ans[i + 1]);
    }
    cout << ans[n] << endl;
    return 0;
}
