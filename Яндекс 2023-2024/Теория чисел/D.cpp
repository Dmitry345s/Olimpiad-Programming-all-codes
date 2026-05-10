#include<bits/stdc++.h>

using namespace std;

int gcd(int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int x1, y1;
    int g = gcd(b % a, a, x1, y1);
    x = y1 - b / a * x1;
    y = x1;
    return g;
}

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int a, b, n, m;
        cin >> a >> b >> n >> m;
        int k, q1;
        int g = gcd(n, m, k, q1);
        if ((b - a) % g != 0) {
            cout << "NO" << endl;
            continue;
        }
        long long u = (b - a) / g;
        long long x0 = a + k * u * n;
        long long p = n * m / g;
        x0 = (x0 % p + p) % p;
        cout << "YES " << x0 << " " << p << endl;
    }
    return 0;
}
