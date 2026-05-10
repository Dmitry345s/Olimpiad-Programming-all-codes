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

long long operator * (Vector a, Vector b) {
    return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

bool check(long long a, long long b) {
    return (a <= 0 && b <= 0) || (a >= 0 && b >= 0);
}

signed main() {
    Point a, o, b, p;
    cin >> a >> o >> b >> p;
    Vector s1 = Vector(o, a), s2 = Vector(o, b), ch = Vector(o, p);
    if (check(s1 * s2, s1 * ch) && check(s2 * s1, s2 * ch)) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
