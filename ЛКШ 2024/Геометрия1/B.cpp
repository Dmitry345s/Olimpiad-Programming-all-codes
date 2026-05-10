#include<bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

struct Vector {
    long long x, y;
    Vector(long long x = 0, long long y = 0) : x(x), y(y) {};
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

long long operator^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

long long operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

signed main() {
    int n;
    cin >> n;
    Point p;
    cin >> p.x >> p.y;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    long double ang = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        Vector v1 = Vector(p, a[i]), v2 = Vector(p, a[j]);
        if (v1 * v2 == 0 && (v1 ^ v2) < 0 || p.x == a[i].x && p.y == a[i].y) {
            cout << "YES" << endl;
            return 0;
        }
        ang += atan2(v1 * v2, v1 ^ v2);
    }
    if (abs(ang) > 3) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
