#include<bits/stdc++.h>

using namespace std;

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

Point mn;

bool cmp2(Point a, Point b) {
    Vector a2 = Vector(mn, a), b2 = Vector(mn, b);
    if (a2 * b2 == 0) {
        return a2.get() < b2.get();
    }
    return a2 * b2 > 0;
}

bool cmp3(Vector a, Vector b, Vector c) {
    if (a * b == 0) {
        return b.get() < c.get();
    }
    return a * b > 0;
}

vector<Point> hull(vector<Point> a) {
    if ((int)a.size() == 1) return a;
    sort(a.begin(), a.end(), cmp);
    mn = a[0];
    a.erase(a.begin());
    int n = (int)a.size();
    sort(a.begin(), a.end(), cmp2);
    vector<Point> ans;
    ans.push_back(mn);
    ans.push_back(a[0]);
    for (int i = 1; i < n; ++i) {
        while ((int)ans.size() > 1 && cmp3(Vector(ans.back(), a[i]), Vector(ans[(int)ans.size() - 2], ans.back()), Vector(ans[(int)ans.size() - 2], a[i]))) {
            ans.pop_back();
        }
        ans.push_back(a[i]);
    }
    return ans;
}

bool point_in_seg(Point a, Point b, Point p) {
    return a == p || b == p || (Vector(a, p) * Vector(b, p) == 0 && (Vector(a, p) ^ Vector(b, p)) < 0);
}

bool point_in_polygon(vector<Point> a, Point p) {
    long double ang = 0;
    int n = (int)a.size();
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (point_in_seg(a[i], a[j], p)) {
            return 1;
        }
        ang += atan2(Vector(p, a[i]) * Vector(p, a[j]), (Vector(p, a[i]) ^ Vector(p, a[j])));
    }
    return ang > 3;
}

bool cmp4(Vector a, Vector b) {
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

signed main() {
    int n, m;
    cin >> n >> m;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i].x >> a[i].y;
    }
    vector<Point> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i].x >> b[i].y;
    }
    a = hull(a);
    b = hull(b);
    n = (int)a.size();
    m = (int)b.size();
    //cout << n << " " << m << endl;
    if (n == 1 && m == 1) {
        cout << "YES" << endl;
        return 0;
    }
    if (n == 1) {
        if (point_in_polygon(b, a[0])) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
        return 0;
    }
    if (m == 1) {
        if (point_in_polygon(a, b[0])) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
        return 0;
    }
    vector<Vector> all;
    for (int i = 0; i < n; ++i) {
        //cout << a[i].x << " " << a[i].y << endl;
        int j = (i + 1) % n;
        all.push_back(Vector(a[i], a[j]));
    }
    for (int i = 0; i < m; ++i) {
        //cout << b[i].x << " " << b[i].y << endl;
        int j = (i + 1) % m;
        all.push_back(Vector(b[j], b[i]));
    }
    Point sec = b[max_element(b.begin(), b.end(), cmp) - b.begin()];
    sec.x *= -1;
    sec.y *= -1;
    Point st = Point(a[0].x + sec.x, a[0].y + sec.y);
    //cout << st.x << " " << st.y << endl;
    sort(all.begin(), all.end(), cmp4);
    vector<Point> pol;
    pol.push_back(st);
    for (int i = 0; i < (int)all.size(); ++i) {
        //cout << all[i].x << " " << all[i].y << endl;
        Point to_add = Point(pol.back().x + all[i].x, pol.back().y + all[i].y);
        while ((int)pol.size() > 1 && Vector(pol.back(), to_add) * Vector(pol[(int)pol.size() - 2], pol.back()) == 0) {
            pol.pop_back();
        }
        pol.push_back(to_add);
    }
    pol.pop_back();
    if (point_in_polygon(pol, Point(0, 0))) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
    return 0;
}
