#include<bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
};

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

struct Vector {
    ll x, y;
    Vector(ll x = 0, ll y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = a.x - b.x;
        y = a.y - b.y;
    }
    ll get2() {
        return x * x + y * y;
    }
};

ll operator * (Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

ll operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool ch3(Point a, Point o, Point b, Point p) {
    if (o.x == p.x && o.y == p.y) return true;
    Vector v1 = Vector(o, a), v2 = Vector(o, b), v3 = Vector(o, p);
    ll x1 = v1 * v2, x2 = v1 * v3, x3 = v2 * v1, x4 = v2 * v3;
    return ((x1 <= 0 && x2 <= 0) || (x1 >= 0 && x2 >= 0)) && ((x3 <= 0 && x4 <= 0) || (x3 >= 0 && x4 >= 0));
}

bool ch2(Point a, Point b, Point c, Point p) {
    return ch3(a, b, c, p) && ch3(b, a, c, p) && ch3(a, c, b, p);
}

bool ch(vector<Point> & a, Point p) {
    int l = 0, r = (int)a.size();
    Vector v1 = Vector(a[0], p);
    while (l + 1 < r) {
        int m = (l + r) / 2;
        Vector v2 = Vector(a[0], a[m]);
        if (v2 * v1 <= 0) {
            r = m;
        } else {
            l = m;
        }
    }
    if (r == (int)a.size()) {
        return 0;
    }
    if (r == 1) {
        if (p == a[0] || p == a[1]) {
            return 1;
        }
        Vector v2 = Vector(a[1], p);
        return v1 * v2 == 0 && (v1 ^ v2) < 0;
    }
    //cout << r << endl;
    return ch2(a[l], a[r], a[0], p);
}

signed main() {
    int n, k, m;
    cin >> n >> m >> k;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        Point p;
        cin >> p;
        cnt += ch(a, p);
        //cout << "! " << cnt << endl;
    }
    if (cnt >= k) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
