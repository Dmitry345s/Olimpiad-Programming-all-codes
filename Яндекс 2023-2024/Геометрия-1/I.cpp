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

struct Line {
    int a, b, c;
    Line(Point f, Point s) {
        a = s.y - f.y;
        b = f.x - s.x;
        c = f.x * (f.y - s.y) + f.y * (s.x - f.x);
    }
};

signed main() {
    Point a, b;
    cin >> a >> b;
    Line l1 = Line(a, b);
    cout << l1.a << " " << l1.b << " " << l1.c << endl;
    return 0;
}
