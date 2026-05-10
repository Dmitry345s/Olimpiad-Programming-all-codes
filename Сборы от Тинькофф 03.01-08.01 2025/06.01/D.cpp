#include<bits/stdc++.h>

#define int long long

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

struct Line {
    int a, b, c;
    Line(Point x, Point y) {
        a = y.y - x.y;
        b = x.x - y.x;
        c = y.x * x.y - y.y * x.x;
    }
    int whr(Point t) {
        return abs((__int128)a * t.x + (__int128)b * t.y + c) / ((__int128)a * t.x + (__int128)b * t.y + c);
    }
};

signed main() {
    int t;
    cin >> t;
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    int q;
    cin >> q;
    int cnt = 0;
    for (int i = 0; i < q; ++i) {
        int x, y;
        cin >> x >> y;
        x = (t * (cnt * cnt * cnt) ^ x);
        y = (t * (cnt * cnt * cnt) ^ y);
        int flag = 0;
        for (int j1 = 0; j1 < n; ++j1) {
            int j2 = (j1 + 1) % n;
            int j3 = (j1 + n / 2) % n;
            int j4 = (j3 + 1) % n;
            Line l1 = Line(a[j1], a[j2]);
            Line l2 = Line(a[j3], a[j4]);
            if (l1.whr(Point(x, y)) <= 0 && l2.whr(Point(x, y)) <= 0) {
                flag = 1;
            }
        }
        if (flag) {
            cout << "YES" << endl;
            cnt++;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
