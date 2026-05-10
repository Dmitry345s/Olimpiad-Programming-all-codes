#include<bits/stdc++.h>

using namespace std;

__int128 x, y;

long long gcd(long long a, long long b) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long d = gcd(b, a % b);
    __int128 x1 = y;
    __int128 y1 = x - (a / b) * y;
    x = x1;
    y = y1;
    return d;
}

signed main() {
    long long a, b, c;
    cin >> a >> b >> c;
    long long d = gcd(a, b);
    if (c % d != 0) {
        cout << "Impossible" << endl;
        return 0;
    }
    //cout << (long long)x << " " << (long long)y << endl;
    x *= (c / d);
    y *= (c / d);
    if (x >= 0) {
        x = x % (b / d);
        y = (c - a * x) / b;
        cout << (long long)x << " " << (long long)y << endl;
    } else {
        x = -x;
        x = (b / d) - x % (b / d);
        if (x == (b / d)) {
            x = 0;
        }
        y = (c - a * x) / b;
        cout << (long long)x << " " << (long long)y << endl;
    }
}
