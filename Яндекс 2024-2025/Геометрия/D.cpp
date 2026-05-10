#include<bits/stdc++.h>

# define int long long

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

istream& operator>> (istream& in, Point& a) {
    in >> a.x >> a.y;
    return in;
}

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int operator^ (Vector a, Vector b) {
    return a.x * b.x + b.y * a.y;
}

bool in_angle(Point o, Point a, Point b, Point p) {
    Vector v1 = Vector(o, a), v2 = Vector(o, b), v3 = Vector(o, p);
    if (p.x == o.x && p.y == o.y) return 1;
    if (v1 * v3 == 0 || v2 * v3 == 0) return 1;
    if ((v1 * v2) == 0) return 0;
    if ((v1 * v2 < 0) == (v1 * v3 < 0) && (v2 * v1 < 0) == (v2 * v3 < 0)) return 1;
    return 0;
}

int ch(Point p, vector<Point>& a, int n) {
    if (!in_angle(a[0], a[1], a[n - 1], p)) return 0;
    int l = 1, r = n - 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (in_angle(a[0], a[l], a[m], p)) {
            r = m;
        } else {
            l = m;
        }
    }
    if (in_angle(a[0], a[l], a[r], p) && in_angle(a[l], a[0], a[r], p) && in_angle(a[r], a[0], a[l], p)) return 1;
    return 0;
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        Point p;
        cin >> p;
        cnt += ch(p, a, n);
    }
    if (cnt >= k) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
