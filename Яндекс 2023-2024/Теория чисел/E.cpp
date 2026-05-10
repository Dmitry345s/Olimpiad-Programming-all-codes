#include<bits/stdc++.h>

using namespace std;

long long gcd(long long a, long long b, long long & x, long long & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    long long x1, y1;
    long long g = gcd(b % a, a, x1, y1);
    x = y1 - b / a * x1;
    y = x1;
    return g;
}

signed main() {
    long long a, m;
    cin >> a >> m;
    long long x, y;
    long long g = gcd(a, m, x, y);
    if (g == 1) {
        cout << (x % m + m) % m << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
