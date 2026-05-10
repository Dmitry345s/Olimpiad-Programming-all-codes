#include<bits/stdc++.h>

#define ld long double

using namespace std;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {};
};

struct Vector {
    ld x, y;
    Vector(ld x = 0, ld y = 0) : x(x), y(y) {};
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    ld get() {
        return sqrtl(x * x + y * y);
    }
    ld operator^ (Vector a) {
        return x * a.x + y * a.y;
    }
};

struct Line {
    ld a, b, c;
    Line(ld a = 0, ld b = 0, ld c = 0) : a(a), b(b), c(c) {};
    Line(Point p1, Point p2) {
        a = p2.y - p1.y;
        b = p1.x - p2.x;
        c = p2.x * p1.y - p2.y * p1.x;
    }
    ld dist(Point p) {
        return (p.x * a + p.y * b + c) / sqrtl(a * a + b * b);
    }
};

bool in(Point a, Point b, Point p) {
    if ((Vector(a, p) ^ Vector(b, p)) <= 0) {
        return 1;
    }
    return 0;
}

ld ch(vector<pair<Point, Point>> a, Point now) {
    ld maxm = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        Line newl = Line(a[i].first, a[i].second);
        //cout << newl.a << " " << newl.b << " " << newl.c << endl;
        ld dist = newl.dist(now);
        //cout << dist << endl;
        Vector per = Vector(-newl.a, -newl.b);
        ld len = per.get();
        per.x /= len;
        per.y /= len;
        per.x *= dist;
        per.y *= dist;
        Point now2 = now;
        now2.x += per.x;
        now2.y += per.y;
        //cout << now.x << " " << now.y << endl;
        if (in(a[i].first, a[i].second, now2)) {
            maxm = max(maxm, abs(dist));
        } else {
            maxm = max(maxm, min(Vector(a[i].first, now).get(), Vector(a[i].second, now).get()));
        }
        //cout << maxm << endl;
        //cout << endl;
    }
    return maxm;
}

ld ch2(ld x, vector<pair<Point, Point>> a) {
    ld l = 0, r = 1e3;
    for (int i = 0; i < 200; ++i) {
        ld m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
        if (ch(a, Point(x, m1)) <= ch(a, Point(x, m2))) {
            r = m2;
        } else {
            l = m1;
        }
    }
    //cout << l << endl;
    return ch(a, Point(x, (l + r) / 2));
}

signed main() {
    int n;
    cin >> n;
    vector<pair<Point, Point>> a(n);
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        a[i].first = Point(x1, y1);
        a[i].second = Point(x2, y2);
    }
    ld l = 0, r = 1e3;
    for (int i = 0; i < 300; ++i) {
        ld m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
        if (ch2(m1, a) <= ch2(m2, a)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    cout.precision(30);
    cout << ch2((l + r) / 2, a) << endl;
}
