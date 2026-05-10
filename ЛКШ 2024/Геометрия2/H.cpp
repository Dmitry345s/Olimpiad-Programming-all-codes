#include<bits/stdc++.h>

using namespace std;

const long double INF = 1e9;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

struct Line {
    long long a, b, c;
    Line(long long a = 0, long long b = 0, long long c = 0) : a(a), b(b), c(c) {};
    Line(Point b1, Point b2) {
        a = b2.y - b1.y;
        b = b1.x - b2.x;
        c = b2.x * b1.y - b2.y * b1.x;
    }
    long double dist(long double d1, long double d2) {
        return abs(a * d1 + b * d2 + c) / sqrtl(a * a + b * b);
    }
};

long double last = 0;

long double ch2(long double x, long double y, vector<Line> a) {
    long double ans = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        ans = max(ans, a[i].dist(x, y));
    }
    return ans;
}

long double ch(long double x, vector<Line> a) {
    long double l = -INF, r = INF;
    for (int i = 0; i < 200; ++i) {
        long double m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
        if (ch2(x, m1, a) < ch2(x, m2, a)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    last = r;
    return ch2(x, r, a);
}

signed main() {
    int n;
    cin >> n;
    //assert(n >= 4);
    vector<Line> lines(n);
    for (int i = 0; i < n; ++i) {
        Point a, b;
        cin >> a.x >> a.y >> b.x >> b.y;
        if (n == 1) {
            cout << a.x << " " << a.y << endl;
            return 0;
        }
        lines[i] = Line(a, b);
        //cout << lines[i].a << " " << lines[i].b << " " << lines[i].c << endl;
    }
    long double l = -INF, r = INF;
    for (int i = 0; i < 200; ++i) {
        long double m1 = (2 * l + r) / 3, m2 = (l + 2 * r) / 3;
        //cout << m1 << " " << m2 << endl;
        if (ch(m1, lines) <= ch(m2, lines)) {
            r = m2;
        } else {
            l = m1;
        }
    }
    ch(r, lines);
    cout << fixed << setprecision(20);
    cout << r << " " << last << endl;
    return 0;
}
