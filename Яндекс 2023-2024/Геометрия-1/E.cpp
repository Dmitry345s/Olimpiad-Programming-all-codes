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

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    int a, b, c;
    Line(int a = 0, int b = 0, int c = 0): a(a), b(b), c(c) {}
    Line(Point f, Point s) {
        a = s.y - f.y;
        b = f.x - s.x;
        c = f.x * (f.y - s.y) + f.y * (s.x - f.x);
    }
};

signed main() {
    Point a1, b1, a2, b2;
    cin >> a1 >> b1 >> a2 >> b2;
    if (Vector(a1, b1) * Vector(a2, b2) == 0) {
        cout << 0 << endl;
        return 0;
    }
    Line l1 = Line(a1, b1), l2 = Line(a2, b2);
    return 0;
}
