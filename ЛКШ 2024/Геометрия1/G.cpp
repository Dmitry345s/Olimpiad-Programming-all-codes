#include<bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {}
};

struct Vector {
    long long x, y;
    Vector(long long x = 0, long long y = 0) : x(x), y(y) {}
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

bool cmp(Point a, Point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
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

bool cmp4(Vector a, Vector b) {
    if ((a.y > 0 || (a.y == 0 && a.x >= 0)) && (b.y < 0 || (b.y == 0 && b.x < 0))) {
        return 1;
    }
    if ((b.y > 0 || (b.y == 0 && b.x >= 0)) && (a.y < 0 || (a.y == 0 && a.x < 0))) {
        return 0;
    }
    return a * b > 0;
}

int get_touch(vector<Vector> & all, Vector x) {
    return (lower_bound(all.begin(), all.end(), x, cmp4) - all.begin()) % (int)all.size();
}

struct Line {
    long long a, b, c;
    Line(long long a = 0, long long b = 0, long long c = 0) : a(a), b(b), c(c) {}
    Line(Point b1, Point b2) {
        a = b2.y - b1.y;
        b = b1.x - b2.x;
        c = b2.x * b1.y - b2.y * b1.x;
    }
    long long dist(Point d) {
        return a * d.x + b * d.y + c;
    }
};

bool check(Point a, Point b, Line c) {
    return (c.dist(a) >= 0 && c.dist(b) <= 0) || (c.dist(a) <= 0 && c.dist(b) >= 0);
}

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    int in = min_element(a.begin(), a.end(), cmp) - a.begin();
    for (int i = 0; i < in; ++i) {
        a.push_back(a[i]);
    }
    reverse(a.begin(), a.end());
    for (int i = 0; i < in; ++i) {
        a.pop_back();
    }
    reverse(a.begin(), a.end());
    int m;
    cin >> m;
    vector<Point> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i].x >> b[i].y;
    }
    sort(b.begin(), b.end(), cmp);
    mn = b[0];
    b.erase(b.begin());
    sort(b.begin(), b.end(), cmp2);
    vector<Point> pol;
    pol.push_back(mn);
    if ((int)b.size() > 0) {
        pol.push_back(b[0]);
        for (int i = 1; i < (int)b.size(); ++i) {
            while ((int)pol.size() > 1 &&
                cmp3(Vector(pol.back(), b[i]), Vector(pol[(int)pol.size() - 2], pol.back()), Vector(pol[(int)pol.size() - 2], b[i]))) {
                pol.pop_back();
            }
            pol.push_back(b[i]);
        }
    }
    vector<Vector> all;
    for (int i = 0; i < (int)pol.size(); ++i) {
        //cout << pol[i].x << " " << pol[i].y << endl;
        int j = (i + 1) % (int)pol.size();
        all.push_back(Vector(pol[i], pol[j]));
    }
    int r = 0;
    long long ans = 0;
    long long rans = 0;
    for (int l = 0; l < n; ++l) {
        //cout << a[l].x << " " << a[l].y << endl;
        if (l == r) {
            r++;
            r %= n;
        }
        while (true) {
            if ((int)pol.size() > 1) {
                Line c = Line(a[l], a[r]);
                int a1 = get_touch(all, Vector(c.b, -c.a));
                int a2 = get_touch(all, Vector(-c.b, c.a));
                //cout << a1 << " " << a2 << endl;
                if (check(pol[a1], pol[a2], c) || Vector(a[l], a[r]) * Vector(a[l], pol[0]) <= 0) {
                    break;
                }
            } else {
                if (Vector(a[l], a[r]) * Vector(a[l], pol[0]) <= 0) {
                    break;
                }
            }
            ans += abs(Vector(a[l], a[r]) * Vector(a[l], a[(r - 1 + n) % n]));
            rans = max(rans, ans);
            //cout << ans << endl;
            r++;
            r %= n;
        }
        //cout << r << endl;
        int next = (l + 1) % n;
        ans -= abs(Vector(a[l], a[next]) * Vector(a[l], a[(r - 1 + n) % n]));
        //cout << ans << endl;
        rans = max(rans, ans);
    }
    cout << rans << endl;
    return 0;
}
