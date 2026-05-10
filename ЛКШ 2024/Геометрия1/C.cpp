#include<bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

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

bool operator== (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

long long operator^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

long long operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int check(const vector<Point> & a, Point p) {
    if (a[0] == p) {
        return 2;
    }
    int n = (int)a.size();
    int l = 1, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (Vector(a[0], a[m]) * Vector(a[0], p) <= 0) {
            r = m;
        } else {
            l = m;
        }
    }
    //cout << l << " " << r << endl;
    if (r == n) {
        return 0;
    }
    Vector v1 = Vector(a[l], p), v2 = Vector(a[r], p);
    if (a[l] == p || a[r] == p || (v1 * v2 == 0 && (v1 ^ v2) < 0)) {
        return 2;
    }
    if (r == n - 1 && (Vector(a[0], p) * Vector(a[r], p) == 0 && (Vector(a[0], p) ^ Vector(a[r], p)) < 0)) {
        return 2;
    }
    if (l == 1 && (Vector(a[0], p) * Vector(a[l], p) == 0 && (Vector(a[0], p) ^ Vector(a[l], p)) < 0)) {
        return 2;
    }
    Vector v3 = Vector(a[l], a[0]), v4 = Vector(a[l], a[r]);
    if ((Vector(a[0], p) * Vector(a[r], p) == 0 && (Vector(a[0], p) ^ Vector(a[r], p)) < 0)) {
        return 1;
    }
    if ((Vector(a[0], p) * Vector(a[l], p) == 0 && (Vector(a[0], p) ^ Vector(a[l], p)) < 0)) {
        return 1;
    }
    if (v3 * v1 < 0 && v3 * v4 < 0 && v1 * v4 < 0 || v3 * v1 > 0 && v3 * v4 > 0 && v1 * v4 > 0) {
        return 1;
    }
    return 0;
}

Point mn;

bool cmp(Point a, Point b) {
    Vector a2 = Vector(mn, a), b2 = Vector(mn, b);
    if (a2 * b2 == 0) {
        return a2.get() < b2.get();
    }
    return a2 * b2 > 0;
}

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    mn = a[0];
    sort(a.begin(), a.end(), cmp);
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        Point p;
        cin >> p.x >> p.y;
        int ch = check(a, p);
        if (ch == 2) {
            cout << "BORDER" << endl;
        } else if (ch == 1) {
            cout << "INSIDE" << endl;
        } else {
            cout << "OUTSIDE" << endl;
        }
    }
    return 0;
}
