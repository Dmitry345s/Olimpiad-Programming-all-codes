#include<bits/stdc++.h>

#define int long long

using namespace std;
using ld = long double;

struct Point {
    int x, y;
    Point (int x = 0, int y = 0) : x(x), y(y) {}
};

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator * (Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

struct Line {
    int a, b, c;
    Line(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {}
    Line(Point u1, Point u2) {
        a = u1.y - u2.y;
        b = u2.x - u1.x;
        c = -(u2.x * u1.y - u2.y * u1.x);
    }
};

pair<ld, ld> inter(Line a, Line b) {
    ld y = (ld)(b.a * a.c - b.c * a.a) / (ld)(a.a * b.b - b.a * a.b);
    ld x = (ld)(b.b * a.c - b.c * a.b) / (ld)(a.b * b.a - b.b * a.a);
    return {x, y};
}

ld dist(pair<ld, ld> a, Point b) {
    ld dx = a.first - b.x;
    ld dy = a.second - b.y;
    return dx * dx + dy * dy;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        Point a, b, c;
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y;
        int ch = 1;
        if (Vector(a, b) * Vector(a, c) < 0) {
            ch *= -1;
            swap(b, c);
        }
        //cout << ch << endl;
        vector<Point> all(3);
        for (int i = 0; i < 3; ++i) {
            cin >> all[i].x >> all[i].y;
        }
        vector<int> to_perm = {0, 1, 2};
        int fl = 0;
        do {
            int ch1 = (Vector(a, all[to_perm[0]]) * Vector(a, all[to_perm[2]]) <= 0);
            int ch2 = (Vector(b, all[to_perm[1]]) * Vector(b, all[to_perm[0]]) <= 0);
            int ch3 = (Vector(c, all[to_perm[2]]) * Vector(c, all[to_perm[1]]) <= 0);
            if (ch1 && ch2 && ch3) {
                Line t1 = Line(a, all[to_perm[0]]), t2 = Line(c, all[to_perm[2]]), t3 = Line(b, all[to_perm[1]]);
                pair<ld, ld> u1 = inter(t1, t2);
                pair<ld, ld> u2 = inter(t1, t3);
                int ch4 = (dist(u1, a) >= dist(u2, a));
                t1 = Line(a, all[to_perm[2]]), t2 = Line(c, all[to_perm[1]]), t3 = Line(b, all[to_perm[0]]);
                pair<ld, ld> u3 = inter(t2, t1);
                pair<ld, ld> u4 = inter(t2, t3);
                int ch5 = (dist(u3, c) <= dist(u4, c));
                /*cout << t1.a << " " << t1.b << " " << t1.c << endl;
                cout << t2.a << " " << t2.b << " " << t2.c << endl;
                cout << t3.a << " " << t3.b << " " << t3.c << endl;
                cout << u1.first << " " << u1.second << " " << u2.first << " " << u2.second << endl;
                cout << to_perm[0] << " " << to_perm[1] << " " << to_perm[2] << " " << ch1 << " " << ch2 << " " << ch3 << " " << ch4 << endl;*/
                if (ch4 && ch5) {
                    fl = 1;
                    break;
                }
            }
        } while (next_permutation(to_perm.begin(), to_perm.end()));
        if (fl) {
            if (ch == -1) {
                swap(to_perm[0], to_perm[2]);
            }
            vector<int> ans(3);
            for (int i = 0; i < 3; ++i) {
                ans[to_perm[i]] = i;
            }
            for (int i = 0; i < 3; ++i) {
                cout << ans[i] + 1 << " ";
            }
            cout << endl;
        } else {
            cout << -1 << " " << -1 << " " << -1 << endl;
        }
    }
    return 0;
}

