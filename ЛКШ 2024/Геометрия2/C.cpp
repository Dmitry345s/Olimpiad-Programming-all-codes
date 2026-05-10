#include<bits/stdc++.h>

using namespace std;

const long long INF = 1e18;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

bool operator== (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

bool cmp(Point a, Point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
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

struct Line {
    long long a, b, c;
    Line(long long a = 0, long long b = 0, long long c = 0) : a(a), b(b), c(c) {};
    Line(Point b1, Point b2) {
        a = b2.y - b1.y;
        b = b1.x - b2.x;
        c = b2.x * b1.y - b1.x * b2.y;
    }
};

long double get_dist(Line b, Point p) {
    long long now = abs(b.a * p.x + b.b * p.y + b.c);
    return (long double)now / sqrtl(b.a * b.a + b.b * b.b);
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    Point mn = a[min_element(a.begin(), a.end(), cmp) - a.begin()];
    vector<Point> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i].x >> b[i].y;
    }
    Point mn2 = b[max_element(b.begin(), b.end(), cmp) - b.begin()];
    mn2.x *= -1;
    mn2.y *= -1;
    Point rst = Point(mn.x + mn2.x, mn.y + mn2.y);
    vector<Vector> all;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        all.push_back(Vector(a[i], a[j]));
    }
    for (int i = 0; i < m; ++i) {
        int j = (i + 1) % m;
        all.push_back(Vector(b[j], b[i]));
    }
    sort(all.begin(), all.end(), cmp2);
    vector<Point> sum;
    sum.push_back(rst);
    for (int i = 0; i < (int)all.size(); ++i) {
        sum.push_back(Point(sum.back().x + all[i].x, sum.back().y + all[i].y));
    }
    long double dist = INF;
    for (int i = 0; i < (int)sum.size(); ++i) {
        int j = (i + 1) % (int)sum.size();
        dist = min(dist, get_dist(Line(sum[i], sum[j]), Point(0, 0)));
    }
    cout << setprecision(20) << max(dist - 60, (long double)0) << endl;
    return 0;
}
