#include<bits/stdc++.h>

using namespace std;
using ld = long double;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
};

struct Vector {
    ld x, y;
    Vector(ld x = 0, ld y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

ld operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

ld dist(Point a, Point b) {
    ld x = a.x - b.x, y = a.y - b.y;
    return sqrtl(x * x + y * y);
}

ld in(int l, int r, int x) {
    if (l <= r) return l <= x && x <= r;
    return (l <= x) || (x <= r);
}

ld dif(int l, int r, vector<ld> & pref) {
    if (l <= r) return pref[r] - pref[l];
    return pref.back() - pref[l] + pref[r];
}

const int LN = 20;

mt19937 rnd(179);

int dc(Point p, vector<Point> & all) {
    int n = (int)all.size();
    int now = rnd() % n;
    for (int i = LN - 1; i >= 0; --i) {
        int j1 = (now + (1 << i)) % n;
        int j2 = ((now - (1 << i)) % n + n) % n;
        if (Vector(p, all[now]) * Vector(p, all[j1]) < 0) {
            now = j1;
        }
        if (Vector(p, all[now]) * Vector(p, all[j2]) < 0) {
            now = j2;
        }
    }
    return now;
}

int uc(Point p, vector<Point> & all) {
    int n = (int)all.size();
    int now = rnd() % n;
    for (int i = LN - 1; i >= 0; --i) {
        int j1 = (now + (1 << i)) % n;
        int j2 = ((now - (1 << i)) % n + n) % n;
        if (Vector(p, all[now]) * Vector(p, all[j1]) > 0) {
            now = j1;
        }
        if (Vector(p, all[now]) * Vector(p, all[j2]) > 0) {
            now = j2;
        }
    }
    return now;
}

signed main() {
    freopen("princess.in", "r", stdin);
    freopen("princess.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    --k;
    vector<Point> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].x >> all[i].y;
    }
    vector<ld> pref(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + dist(all[i], all[(i + 1) % n]);
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        Point p;
        cin >> p.x >> p.y;
        int l = uc(p, all);
        int r = dc(p, all);
        //cout << l << " " << r << endl;
        if (in(l, r, k)) {
            cout << setprecision(20) << dist(all[k], p) << endl;
        } else {
            cout << setprecision(20) << min(dist(p, all[l]) + dif(k, l, pref), dist(p, all[r]) + dif(r, k, pref)) << endl;
        }
    }
    return 0;
}
