#include<bits/stdc++.h>

#define int long long

using namespace std;

int mod = 1000000007;

int mpow(int a, int x) {
    if (x == 0) return 1ll;
    //cout << a << " " << x << endl;
    int k = mpow((a * a) % mod, x / 2);
    if (x % 2 == 1) {
        return (a * k) % mod;
    }
    return k;
}

signed main() {
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
    }
    if (n == 2) {
        cout << mpow(4, d) << endl;
    }
    return 0;
}
