#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MOD = 1e8 + 7;

int f(int n) {
    int copn = n;
    int ans = 1;
    for (int i = 2; i * i <= copn; ++i) {
        if (n % i != 0) continue;
        int one = 1;
        int second = i;
        n /= i;
        while (n % i == 0) {
            one *= i;
            second *= i;
            n /= i;
        }
        ans *= (second - one);
    }
    if (n != 1) {
        ans *= (n - 1);
    }
    return ans;
}

signed main() {
    int n, k;
    cin >> n >> k;
    int cnt = (k + 1) / 2;
    for (int i = 0; i < cnt; ++i) {
        n = f(n);
        if (n == 1) {
            cout << 1 << endl;
            return 0;
        }
    }
    //assert(n < MOD);
    n %= MOD;
    cout << n << endl;
    return 0;
}
