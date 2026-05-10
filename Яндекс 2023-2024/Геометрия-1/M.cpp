#include<bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0): x(x), y(y) {}
};

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

struct Vector {
    int x, y;
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

double get_angle(Vector a, Vector b) {
    return atan2(a * b, (a ^ b));
}

signed main() {
    Point a, b, c;
    cin >> a >> b >> c;
    Vector v1 = Vector(a, b), v2 = Vector(a, c), v3 = Vector(b, a), v4 = Vector(b, c);
    Vector v5 = Vector(c, a), v6 = Vector(c, b);
    double mx = max(max(abs(get_angle(v1, v2)), abs(get_angle(v3, v4))), abs(get_angle(v5, v6)));
    cout << setprecision(20) << mx / M_PI * 180 << endl;
    return 0;
}
