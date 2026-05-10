#include<bits/stdc++.h>

using namespace std;

__int128 gcd(__int128 a, __int128 b, __int128 & x, __int128 & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    __int128 x1, y1;
    __int128 g = gcd(b % a, a, x1, y1);
    x = y1 - b / a * x1;
    y = x1;
    return g;
}

signed main() {
    long long t, n, m, k;
    cin >> t >> n >> m >> k;
    while (t--) {
        long long a1, a2, a3, b1, b2, b3;
        cin >> a1 >> a2 >> a3 >> b1 >> b2 >> b3;
        __int128 c1 = b1 - a1, c2 = a2 - b2, c3 = b3 - a3;
        __int128 x1, y1;
        __int128 g = gcd(n, k, x1, y1);
        if ((c3 - c1) % g != 0) {
            cout << "NO" << endl;
            continue;
        }
        __int128 x2, y2;
        __int128 g2 = gcd(n, m, x2, y2);
        if ((c2 - c1) % g2 != 0) {
            cout << "NO" << endl;
            continue;
        }
        __int128 x3, y3;
        __int128 g3 = gcd(m, k, x3, y3);
        if ((c2 - c3) % g3 != 0) {
            cout << "NO" << endl;
            continue;
        }
        cout << "YES" << endl;
    }
    return 0;
}
