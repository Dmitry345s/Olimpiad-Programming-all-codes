#include<bits/stdc++.h>

#define int long long

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector (Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    int get() {
        return x * x + y * y;
    }
};

int operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

Point mn;

bool cmp(Point a, Point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool cmp2(Point a, Point b) {
    Vector va = Vector(mn, a), vb = Vector(mn, b);
    if (va * vb == 0) {
        return va.get() < vb.get();
    }
    return va * vb > 0;
}

bool cmp3(Point a, Point b, Point c) {
    Vector v1 = Vector(b, c);
    Vector v2 = Vector(a, b);
    if (v1 * v2 == 0) {
        return Vector(a, c).get() > Vector(a, b).get();
    }
    return v1 * v2 > 0;
}

long double hull(vector<Point> a) {
    if ((int)a.size() < 2) {
        return 0;
    }
    sort(a.begin(), a.end(), cmp);
    mn = a[0];
    a.erase(a.begin());
    sort(a.begin(), a.end(), cmp2);
    vector<Point> hl;
    hl.push_back(mn);
    hl.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
        while ((int)hl.size() >= 2 && cmp3(hl[(int)hl.size() - 2], hl.back(), a[i])) {
            hl.pop_back();
        }
        hl.push_back(a[i]);
    }
    long double ans = 0;
    for (int i = 0; i < (int)hl.size(); ++i) {
        //cout << hl[i].x << " " << hl[i].y << endl;
        int j = (i + 1) % (int)hl.size();
        ans += sqrtl(Vector(hl[i], hl[j]).get());
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    const long double INF = 2e18;
    vector<long double> b(n + 1, INF);
    for (int i = 0; i < (1 << n); ++i) {
        vector<Point> to_ch;
        int cnt = 0;
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) {
                to_ch.push_back(a[j]);
                cnt++;
            }
        }
        //cout << i << endl;
        b[cnt] = min(b[cnt], hull(to_ch));
    }
    cout.precision(20);
    for (int i = 1; i <= n; ++i) {
        cout << b[i] << endl;
    }
    return 0;
}
