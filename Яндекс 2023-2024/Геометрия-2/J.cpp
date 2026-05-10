#include<bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
};

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

struct Vector {
    ll x, y;
    Vector(ll x, ll y) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    ll get() {
        return x * x + y * y;
    }
};

ll operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

ll operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

Point c;

bool cmp(Point a = Point(), Point b = Point()) {
    Vector v1 = Vector(c, a), v2 = Vector(c, b);
    if (v1 * v2 == 0) {
        return v1.get() < v2.get();
    }
    return v1 * v2 < 0;
}

signed main() {
    int n;
    cin >> n;
    cin >> c;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end(), cmp);
    int flag = 0;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        Vector v1 = Vector(c, a[i]), v2 = Vector(c, a[j]);
        if ((v1 * v2 == 0 && ((v1 ^ v2) < 0 || j == 0)) || v2 * v1 < 0) {
            flag = 1;
        }
    }
    if (flag) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
