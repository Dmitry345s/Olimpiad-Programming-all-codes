#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int a, b;
    cin >> a >> b;
    int u = b - a;
    if (u == 0) {
        if (a == 1) {
            cout << 2 << " " << 4 << endl;
            return 0;
        }
        if (a == 2) {
            cout << 3 << " " << 6 << endl;
            return 0;
        }
        if (a == 3) {
            cout << 4 << " " << 8 << endl;
            return 0;
        }
        int x = 2, y = -1;
        int b2 = b / x;
        int t = 2;
        while (t * t <= b2) {
            if (b2 % t == 0) {
                y = x * t;
                break;
            }
            t++;
        }
        if (y == -1) {
            y = x * b2;
        }
        cout << x << " " << y << endl;
        return 0;
    }
    int t = 2;
    int x = -1, y = -1;
    while (t * t <= u) {
        if (u % t == 0) {
            x = t;
            break;
        }
        t++;
    }
    if (x == -1) {
        x = u;
    }
    int b2 = b / x;
    t = 2;
    while (t * t <= b2) {
        if (b2 % t == 0) {
            y = x * t;
            break;
        }
        t++;
    }
    if (y == -1) {
        y = x * b2;
    }
    if (x >= y || x == 1) {
        cout << -1 << " " << -1 << endl;
        return 0;
    }
    cout << x << " " << y << endl;
}
