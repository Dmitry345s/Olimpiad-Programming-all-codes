#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 998244353;

int fpow(int a, int x) {
    a %= MOD;
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
    int n;
    cin >> n;
    cout << fpow(n, n - 1) << endl;
    return 0;
}
