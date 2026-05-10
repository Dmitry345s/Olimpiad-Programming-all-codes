#include<bits/stdc++.h>

using namespace std;

const int LN = 19;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

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

bool cmp(Vector a, Vector b) {
    return a * b > 0;
}

pair<int, int> get_ans(const vector<Point> & a, Point p) {
    int n = (int)a.size();
    int now = 0;
    for (int i = LN; i >= 0; --i) {
        int j1 = ((now - (1 << i)) % n + n) % n;
        int j2 = (now + (1 << i)) % n;
        if (cmp(Vector(p, a[j1]), Vector(p, a[now]))) {
            now = j1;
        }
        if (cmp(Vector(p, a[j2]), Vector(p, a[now]))) {
            now = j2;
        }
    }
    int now1 = 0;
    for (int i = LN; i >= 0; --i) {
        int j1 = ((now1 - (1 << i)) % n + n) % n;
        int j2 = (now1 + (1 << i)) % n;
        if (!cmp(Vector(p, a[j1]), Vector(p, a[now1]))) {
            now1 = j1;
        }
        if (!cmp(Vector(p, a[j2]), Vector(p, a[now1]))) {
            now1 = j2;
        }
    }
    return {now1, now};
}

bool check(int l, int r, int k, int sz) {
    if (l <= r) {
        return l <= k && k <= r;
    }
    return l <= k && k <= sz || 0 <= k && k <= r;
}

long double get_pref(const vector<long double> & pref, int l, int r, int n) {
    if (l == r) {
        return 0;
    }
    if (l < r) {
        return pref[r] - pref[l];
    }
    return pref[n] - pref[l] + pref[r];
}

signed main() {
    int n, k;
    cin >> n >> k;
    --k;
    vector<Point> a(n);
    vector<long double> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    pref[1] = sqrtl(Vector(a[0], a[1]).get());
    for (int i = 2; i <= n; ++i) {
        pref[i] = pref[i - 1] + sqrtl(Vector(a[i - 1], a[(i) % n]).get());
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        Point p;
        cin >> p.x >> p.y;
        auto [l, r] = get_ans(a, p);
        //cout << l << " " << r << endl;
        if (check(l, r, k, n)) {
            cout << setprecision(20) << sqrtl(Vector(p, a[k]).get()) << endl;
        } else {
            cout << setprecision(20) << min(get_pref(pref, r, k, n) + sqrtl(Vector(p, a[r]).get()), get_pref(pref, k, l, n) + sqrtl(Vector(p, a[l]).get())) << endl;
        }
    }
    return 0;
}
