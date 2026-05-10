#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MOD = 100000007;

int ph(int x) {
    int ans = 1;
    int u = x;
    for (int i = 2; i * i <= x; ++i) {
        if (u % i == 0) {
            ans *= (i - 1);
            u /= i;
        }
        while (u % i == 0) {
            u /= i;
            ans *= i;
        }
    }
    if (u != 1) {
        ans *= (u - 1);
    }
    return ans;
}

signed main() {
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < (k + 1) / 2; ++i) {
        n = ph(n);
        if (n == 1) break;
    }
    cout << n % MOD << endl;
    return 0;
}
