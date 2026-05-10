#include<bits/stdc++.h>

using namespace std;

struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0) : x(x), y(y) {};
};

struct Vector {
    long double x, y;
    Vector(long double x = 0, long double y = 0) : x(x), y(y) {};
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    long double get() {
        return sqrtl(x * x + y * y);
    }
};

struct Line {
    long double a, b, c;
    Line(long double a = 0, long double b = 0, long double c = 0) : a(a), b(b), c(c) {};
    Line(Point b1, Point b2) {
        a = b2.y - b1.y;
        b = b1.x - b2.x;
        c = b2.x * b1.y - b1.x * b2.y;
    }
};

Point ver(Line a, Line b) {
    Point ans;
    ans.y = (a.c * b.a - b.c * a.a) / (b.b * a.a - a.b * b.a);
    ans.x = (a.c * b.b - b.c * a.b) / (b.a * a.b - a.a * b.b);
    return ans;
}

struct Circle {
    long double x, y, r;
    Circle(long double x = 0, long double y = 0, long double r = 0) : x(x), y(y), r(r) {};
    Circle(Point a, Point b) {
        x = (a.x + b.x) / 2;
        y = (a.y + b.y) / 2;
        r = sqrtl((a.x - x) * (a.x - x) + (a.y - y) * (a.y - y));
    }
    Circle(Point a, Point b, Point c) {
        Point m1 = Point((a.x + b.x) / 2, (a.y + b.y) / 2);
        Vector v1 = Vector(a, b);
        Vector v2 = Vector(-v1.y, v1.x);
        Point p1 = Point(m1.x + v2.x, m1.y + v2.y);
        Line l1 = Line(m1, p1);
        Point m2 = Point((a.x + c.x) / 2, (a.y + c.y) / 2);
        Vector v3 = Vector(a, c);
        Vector v4 = Vector(-v3.y, v3.x);
        Point p2 = Point(m2.x + v4.x, m2.y + v4.y);
        Line l2 = Line(m2, p2);
        Point o = ver(l1, l2);
        r = Vector(o, a).get();
        x = o.x;
        y = o.y;
    }
};

bool in_circle(Circle a, Point p) {
    long double x = p.x - a.x, y = p.y - a.y;
    return a.r >= sqrtl(x * x + y * y);
}

mt19937 rnd(228);

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    shuffle(a.begin(), a.end(), rnd);
    Circle st;
    for (int i = 0; i < n; ++i) {
        if (in_circle(st, a[i])) continue;
        st = Circle(a[i].x, a[i].y, 0);
        for (int j = 0; j < i; ++j) {
            if (in_circle(st, a[j])) continue;
            st = Circle(a[i], a[j]);
            for (int k = 0; k < j; ++k) {
                if (in_circle(st, a[k])) continue;
                st = Circle(a[i], a[j], a[k]);
            }
        }
    }
    cout << setprecision(20) << st.x << " " << st.y << endl << st.r << endl;
    return 0;
}
