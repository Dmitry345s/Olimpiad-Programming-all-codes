#include<bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

bool cmp(Point a, Point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool operator== (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

struct Vector {
    long long x, y;
    Vector(long long x = 0, long long y = 0) : x(x), y(y) {};
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    long long get() {
        return x * x + y * y;
    }
};

long long operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

long long operator^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool cmp2(Vector a, Vector b) {
    if ((a.y > 0 || (a.y == 0 && a.x >= 0)) && (b.y < 0 || (b.y == 0 && b.x < 0))) {
        return 1;
    }
    if ((b.y > 0 || (b.y == 0 && b.x >= 0)) && (a.y < 0 || (a.y == 0 && a.x < 0))) {
        return 0;
    }
    if (a * b == 0) {
        return a.get() < b.get();
    }
    return a * b > 0;
}

bool in_seg(Point a, Point b, Point p) {
    return (a == p || b == p || (Vector(a, p) * Vector(b, p) == 0 && (Vector(a, p) ^ Vector(b, p)) < 0));
}

bool in_angle(Point a, Point o, Point b, Point p) {
    Vector v1 = Vector(o, a), v2 = Vector(o, b), v3 = Vector(o, p);
    return (v1 * v3 < 0 && v1 * v2 < 0 && v3 * v2 < 0) || (v1 * v3 > 0 && v1 * v2 > 0 && v3 * v2 > 0);
}

bool ch(const vector<Point> & a, Point p) {
    int n = (int)a.size();
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (Vector(a[0], p) * Vector(a[0], a[m]) >= 0) {
            r = m;
        } else {
            l = m;
        }
    }
    if (r == n) {
        return 0;
    }
    if (l == 0) {
        return in_seg(a[0], a[1], p);
    }
    return in_seg(a[0], a[l], p) || in_seg(a[0], a[r], p) || in_seg(a[l], a[r], p) || in_angle(a[0], a[l], a[r], p);
}

signed main() {
    int n1, n2, n3;
    cin >> n1;
    vector<Point> a(n1);
    Point mn;
    for (int i = 0; i < n1; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    mn = a[min_element(a.begin(), a.end(), cmp) - a.begin()];
    cin >> n2;
    vector<Point> b(n2);
    Point mn2;
    for (int i = 0; i < n2; ++i) {
        cin >> b[i].x >> b[i].y;
    }
    mn2 = b[min_element(b.begin(), b.end(), cmp) - b.begin()];
    cin >> n3;
    vector<Point> c(n3);
    Point mn3;
    for (int i = 0; i < n3; ++i) {
        cin >> c[i].x >> c[i].y;
    }
    mn3 = c[min_element(c.begin(), c.end(), cmp) - c.begin()];
    Point rst;
    rst.x = mn.x + mn2.x + mn3.x;
    rst.y = mn.y + mn2.y + mn3.y;
    vector<Vector> all;
    for (int i = 0; i < n1; ++i) {
        int j = (i + 1) % n1;
        all.push_back(Vector(a[i], a[j]));
    }
    for (int i = 0; i < n2; ++i) {
        int j = (i + 1) % n2;
        all.push_back(Vector(b[i], b[j]));
    }
    for (int i = 0; i < n3; ++i) {
        int j = (i + 1) % n3;
        all.push_back(Vector(c[i], c[j]));
    }
    sort(all.begin(), all.end(), cmp2);
    vector<Point> pol;
    pol.push_back(rst);
    for (int i = 0; i < (int)all.size(); ++i) {
        Point to_add = Point(pol.back().x + all[i].x, pol.back().y + all[i].y);
        while ((int)pol.size() > 1 && Vector(pol[(int)pol.size() - 2], pol.back()) * Vector(pol.back(), to_add) == 0) {
            pol.pop_back();
        }
        pol.push_back(to_add);
    }
    pol.pop_back();
    for (int i = 0; i < (int)pol.size(); ++i) {
        //cout << pol[i].x << " " << pol[i].y << endl;
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        Point p;
        cin >> p.x >> p.y;
        p.x *= 3;
        p.y *= 3;
        if (ch(pol, p)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
