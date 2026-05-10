#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    int d;
    cin >> d;
    if (n > m) {
        swap(n, m);
    }
    for (int i = 0; i < min(__gcd(n, m), 1ll * 1000000); ++i) {
        cout << d;
    }
    cout << endl;
    /*int a = 0;
    int b = 0;
    for (int i = 0; i < n; ++i) {
        a *= 10;
        a += d;
    }
    for (int i = 0; i < m; ++i) {
        b *= 10;
        b += d;
    }
    //assert(__gcd(a, b) == a);
    cout << __gcd(a, b) << endl;*/
    return 0;
}
