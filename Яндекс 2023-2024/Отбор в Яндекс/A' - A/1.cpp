#include<bits/stdc++.h>
#define int long double

using namespace std;

int EPS = 1e-6;

struct Point {
    int x, y;
    Point (int a = 1e9, int b = 1e9) {
        x = a;
        y = b;
    }
};

struct Vector {
    int x, y;
    Vector (int a, int b) {
        x = a;
        y = b;
    }
    Vector (Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

struct Line {
    int a, b, c;
    Line (int ta, int tb, int tc) {
        a = ta;
        b = tb;
        c = tc;
        int tmp = sqrt(a * a + b * b);
        a /= tmp;
        b /= tmp;
        c /= tmp;
    }
    Line (Point x, Point y) {
        a = x.y - y.y;
        b = y.x - x.x;
        c = x.x * y.y - y.x * x.y;
        int tmp = sqrt(a * a + b * b);
        a /= tmp;
        b /= tmp;
        c /= tmp;
    }
};

bool equals(int a, int b) {
    return abs(a - b) < EPS;
}

int operator * (Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

int operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

istream & operator >> (istream & in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

ostream & operator << (ostream & out, Point a) {
    out << a.x << " " << a.y;
    return out;
}
int get(Vector a) {
    return sqrt(a.x * a.x + a.y * a.y);
}

Point now;

bool cmp(Point a, Point b) {
    int k = Vector(now, a) * Vector(now, b);
    if (k == 0) {
        return get(Vector(now, a)) < get(Vector(now, b));
    }
    return k > 0;
}

signed main() {
    Point x;
    int n;
    cin >> n;
    cin >> x;
    vector<Point> a(n);
    int ch = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (!i) now = a[i];
        if (a[i].y < now.y) {
            now = a[i];
            ch = i;
        }
        if (a[i].y == now.y && a[i].x < now.x) {
            now = a[i];
            ch = i;
        }
    }
    vector<Point> obl;
    while ((obl.size() < 3 || !(obl.back().x == obl[0].x && obl.back().y == obl[0].y)) && a.size() >= 1) {
        sort(a.begin(), a.end(), cmp);
        now = a[0];
        if (obl.size() <= 1) {
            obl.push_back(a[0]);
        } else {
            if (Vector(obl[obl.size() - 2], obl.back()) * Vector(obl.back(), a[0]) == 0) {
                obl.pop_back();
            }
            obl.push_back(a[0]);
        }
        if (obl.size() != 1) {
            swap(a[0], a.back());
            a.pop_back();
        } else {
            now = a[1];
        }
    }
    int ans = 0;
    for (int i = 0; i < obl.size() - 1; ++i) {
        Line s = Line(obl[i], obl[i + 1]);
        Vector norm = Vector(-s.a, -s.b);
        int d = s.a * x.x + s.b * x.y + s.c;
        Point f = Point(x.x + norm.x * d, x.y + norm.y * d);
        int cnst = (Vector(f, obl[i]) * Vector(f, obl[i + 1]));
        if (equals(cnst, 0) && (min(obl[i].x, obl[i + 1].x) < f.x && f.x < max(obl[i].x, obl[i + 1].x) ||
                                f.x == obl[i].x && f.x == obl[i + 1].x && min(obl[i].y, obl[i + 1].y) < f.y && f.y < max(obl[i].y, obl[i + 1].y))) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
