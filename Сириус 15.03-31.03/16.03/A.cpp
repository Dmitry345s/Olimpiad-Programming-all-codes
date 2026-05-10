#include<bits/stdc++.h>

//#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<long long> cnt(m);
    vector<long long> minm(5, 1e15);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        cnt[i] = a * 100 + b;
        minm[(5 - cnt[i] % 5) % 5] = min(minm[(5 - cnt[i] % 5) % 5], cnt[i]);
    }
    int const mx = 3e6;
    long long d[mx];
    long long ch2[mx + 1];
    for (int i = 0; i < mx; ++i) {
        d[i] = 1e15;
        ch2[i] = 1e15;
    }
    d[0] = 0;
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < mx - i; ++j) {
            d[j + i] = min(d[j + i], d[j] + minm[i]);
        }
    }
    ch2[mx] = 1e15;
    for (int i = mx - 1; i >= 0; --i) {
        ch2[i] = min(ch2[i + 1], d[i]);
    }
    long long ans = 1e15;
    for (int i = 1; i < mx; ++i) {
        if (d[i] != 1e15) {
            ans = min(ans, n / i * d[i] + ch2[n % i]);
        }
    }
    if (n == 0) {
        cout << 0 << " " << 0 << endl;
        return 0;
    }
    if (ans == 1e15) {
        cout << -1 << endl;
        return 0;
    }
    cout << ans / 100 << " " << ans % 100 << endl;
    return 0;
}
