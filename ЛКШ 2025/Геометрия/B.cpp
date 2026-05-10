#include<bits/stdc++.h>

using namespace std;
using ld = long double;

const ld EPS = 1e-5;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
};

bool operator < (Point a, Point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

struct Line {
    ld a, b, c;
    Line(ld a = 0, ld b = 0, ld c = 0) : a(a), b(b), c(c) {}
    Line(Point x, Point y) {
        a = x.y - y.y;
        b = y.x - x.x;
        c = y.y * x.x - x.y * y.x;
    }
    ld get(Point u) {
        return a * u.x + b * u.y + c;
    }
};

ld dist(Point a, Point b) {
    ld x = a.x - b.x, y = a.y - b.y;
    return sqrtl(x * x + y * y);
}

Point intersect(Line a, Line b) {
    //if ((b.b * a.a - b.a * a.b) == 0) return Point(1e7, 1e7);
    return Point((-b.b * a.c + b.c * a.b) / (b.b * a.a - b.a * a.b), (-b.a * a.c + b.c * a.a) / (b.a * a.b - b.b * a.a));
}

struct Circle {
    Point cn;
    ld r;
    Circle(Point cn, ld r = 0) : cn(cn), r(r) {}
    Circle(Point a, Point b) {
        cn = Point((a.x + b.x) / 2, (a.y + b.y) / 2);
        r = dist(a, b) / 2;
    }
    Circle(Point a, Point b, Point c) {
        Line st1 = Line(a, b);
        Line st2 = Line(a, c);
        //cout << st1.a << " " << st1.b << " " << st1.c << endl;
        //cout << st2.a << " " << st2.b << " " << st2.c << endl;
        Point c1 = Point((a.x + b.x) / 2, (a.y + b.y) / 2);
        Point c2 = Point((a.x + c.x) / 2, (a.y + c.y) / 2);
        Point c3 = Point(c1.x + st1.a, c1.y + st1.b);
        Point c4 = Point(c2.x + st2.a, c2.y + st2.b);
        //cout << c1.x << " " << c1.y << " " << c3.x << " " << c3.y << endl;
        //cout << c2.x << " " << c2.y << " " << c4.x << " " << c4.y << endl;
        st1 = Line(c1, c3);
        st2 = Line(c2, c4);
        //cout << st1.a << " " << st1.b << " " << st1.c << endl;
        //cout << st2.a << " " << st2.b << " " << st2.c << endl;
        cn = intersect(st1, st2);
        r = dist(cn, a);
    }
    int ch(Point a) {
        return dist(cn, a) - r <= EPS;
    }
};

mt19937 rnd(179);

signed main() {
    freopen("circlecover.in", "r", stdin);
    freopen("circlecover.out", "w", stdout);
    int n;
    cin >> n;
    vector<Point> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].x >> all[i].y;
    }
    Circle ch = Circle(all[0], all[1], all[2]);
    //cout << ch.cn.x << " " << ch.cn.y << " " << ch.r << endl;
    shuffle(all.begin(), all.end(), rnd);
    //sort(all.begin(), all.end());
    Circle now = Circle(Point(1e7, 1e7), 0);
    for (int i = 0; i < n; ++i) {
        if (!now.ch(all[i])) {
            now = Circle(all[i]);
            for (int j = 0; j < i; ++j) {
                if (!now.ch(all[j])) {
                    now = Circle(all[i], all[j]);
                    for (int k = 0; k < j; ++k) {
                        if (!now.ch(all[k])) {
                            now = Circle(all[i], all[j], all[k]);
                        }
                        //cout << i << " " << j << " " << k << " " << now.cn.x << " " << now.cn.y << " " << now.r << endl;
                    }
                }
            }
        }
    }
    cout << setprecision(20) << now.cn.x << " " << now.cn.y << endl;
    cout << setprecision(20) << now.r << endl;
    return 0;
}
