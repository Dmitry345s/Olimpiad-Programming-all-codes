#include<bits/stdc++.h>

using namespace std;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

struct Line {
    double a, b, c;
    Line(double a = 0, double b = 0, double c = 0) : a(a), b(b), c(c) {}
    Line(Point a1, Point a2) {
        a = a2.x - a1.x;
        b = a1.y - a2.y;
        c = a1.x * a2.y - a2.x * a1.y;
    }
    double get(double x) {
        return (-b * x - c) / a;
    }
};

bool ch(vector<Point> a, double m) {
    int ch1 = 1, ch2 = 1;
    int n = (int)a.size();
    for (int i = 0; i < n; ++i) {
        if (a[i].x < m) {
            ch1 = 0;
        } else if (a[i].x > m) {
            ch2 = 0;
        }
    }
    if (ch1 == 0 && ch2 == 1) {
        return 0;
    } else if (ch2 == 0 && ch1 == 1) {
        return 1;
    }
    vector<Point> tr, tr2;
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        if (a[i].x < m) {
            tr.push_back(a[i]);
        } else if (a[i].x > m) {
            tr2.push_back(a[i]);
        }
        if (a[i].x < m && m <= a[j].x) {
            Point k = Point(m, Line(a[i], a[j]).get(m));
            tr.push_back(k);
            tr2.push_back(k);
        }
        if (a[j].x < m && m <= a[i].x) {
            Point k = Point(m, Line(a[i], a[j]).get(m));
            tr.push_back(k);
            tr2.push_back(k);
        }
    }
    long double s1 = 0, s2 = 0;
    //cout << "! " << m << endl;
    for (int i = 0; i < (int)tr.size(); ++i) {
        //cout << tr[i].x << " " << tr[i].y << endl;
        int j = (i + 1) % (int)tr.size();
        s1 += (tr[i].x + tr[j].x) * (tr[i].y - tr[j].y);
    }
    s1 = abs(s1);
    for (int i = 0; i < (int)tr2.size(); ++i) {
        //cout << tr2[i].x << " " << tr2[i].y << endl;
        int j = (i + 1) % (int)tr2.size();
        s2 += (tr2[i].x + tr2[j].x) * (tr2[i].y - tr2[j].y);
    }
    s2 = abs(s2);
    return s1 <= s2;
}

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    double l = -1e3 - 1, r = 1e3 + 1;
    for (int _ = 0; _ < 1000; ++_) {
        //cout << l << " " << r << endl;
        double m = (l + r) / 2;
        if (ch(a, m)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << setprecision(20) << l << endl;
    return 0;
}
