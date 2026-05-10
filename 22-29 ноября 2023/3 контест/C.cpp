#include<bits/stdc++.h>

using namespace std;

struct Point {
    int x, y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(int x1, int y1) {
        x = x1;
        y = y1;
    }
};

struct Vector {
    int x, y;
    Vector(int x1, int y1) {
        x = x1;
        y = y1;
    }
    Vector(Point a) {
        x = a.x;
        y = a.y;
    }
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

int operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool operator < (Point a, Point b) {
    if (a.x == b.x) {
        return a.y < b.y;
    }
    return a.x < b.x;
}

istream & operator >> (istream & in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

bool bounding_box(Point a, Point b, Point c, Point d) {
    bool ch = !(b.x < c.x || a.x > d.x);
    if (a.x == b.x && a.x == c.x && c.x == d.x) {
        return !(max(b.y, a.y) < min(c.y, d.y) || min(a.y, b.y) > max(c.y, d.y));
    }
    return ch;
}

mt19937 rnd(time(0));

bool ch(Point a, Point b, Point c, Point d) {
    Vector v1 = Vector(a, b), v2 = Vector(a, c), v3 = Vector(a, d);
    if (v1 * v2 == 0 && v1 * v3 == 0) {
        return !bounding_box(min(a, b), max(a, b), min(c, d), max(c, d));
    } else {
        Vector v4 = Vector(b, a), v5 = Vector(b, c), v6 = Vector(b, d);
        if ((v2 * v1) * (v3 * v1) <= 0 && (v4 * v6) * (v5 * v6) <= 0) {
            return 0;
        } else {
            return 1;
        }
    }
}

signed main() {
    int p, n;
    cin >> p >> n;
    vector<pair<Point, Point>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        pair<Point, Point> one = {a[i].first, Point(a[i].first.x, a[i].second.y)};
        pair<Point, Point> second = {a[i].first, Point(a[i].second.x, a[i].first.y)};
        int cnt = 1, cnt2 = 1;
        for (int j = 0; j < n; ++j) {
            if (j == i) continue;
            cnt = (cnt & ch(Point(0, 0), one.first, a[j].first, Point(a[j].first.x, a[j].second.y)));
            cnt = (cnt & ch(Point(0, 0), one.second, a[j].first, Point(a[j].first.x, a[j].second.y)));
            cnt = (cnt & ch(one.first, one.second, a[j].first, Point(a[j].first.x, a[j].second.y)));
            cnt = (cnt & ch(Point(0, 0), one.first, a[j].first, Point(a[j].second.x, a[j].first.y)));
            cnt = (cnt & ch(Point(0, 0), one.second, a[j].first, Point(a[j].second.x, a[j].first.y)));
            cnt = (cnt & ch(one.first, one.second, a[j].first, Point(a[j].second.x, a[j].first.y)));
            cnt2 = (cnt2 & ch(Point(0, 0), second.first, a[j].first, Point(a[j].first.x, a[j].second.y)));
            cnt2 = (cnt2 & ch(Point(0, 0), second.second, a[j].first, Point(a[j].first.x, a[j].second.y)));
            cnt2 = (cnt2 & ch(second.first, second.second, a[j].first, Point(a[j].first.x, a[j].second.y)));
            cnt2 = (cnt2 & ch(Point(0, 0), second.first, a[j].first, Point(a[j].second.x, a[j].first.y)));
            cnt2 = (cnt2 & ch(Point(0, 0), second.second, a[j].first, Point(a[j].second.x, a[j].first.y)));
            cnt2 = (cnt2 & ch(second.first, second.second, a[j].first, Point(a[j].second.x, a[j].first.y)));
        }
        if (cnt | cnt2) {
            ans += 1;
        }
    }
    if (p == 1) {
        cout << ans << endl;
    } else {
        cout << (n + p) / 2 << endl;
    }
    return 0;
}
