#include<bits/stdc++.h>

# define int long long

using namespace std;

int gcd(int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int k = gcd(b % a, a, x, y);
    swap(x, y);
    x -= b / a * y;
    return k;
}

signed main() {
    int a, b, c;
    cin >> a >> b >> c;
    int x = 0, y = 0;
    int d = gcd(a, b, x, y);
    if (c % d != 0) {
        cout << "Impossible" << endl;
        return 0;
    }
    int u = a * b / d;
    int dela = u / a;
    int delb = u / b;
    x *= (c / d);
    y *= (c / d);
    if (x < 0) {
        int up = (-x + dela - 1) / dela;
        x += dela * up;
        y -= delb * up;
    } else {
        int down = x / dela;
        x -= dela * down;
        y += delb * down;
    }
    cout << x << " " << y << endl;
    return 0;
}
