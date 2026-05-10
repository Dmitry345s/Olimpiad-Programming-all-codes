#include<bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
};


istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

struct Vector {
    ll x, y;
    Vector(ll x = 0, ll y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    ll get() {
        return x * x + y * y;
    }
};

ll operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

ll operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

struct Line {
    __int128 a, b, c;
    Line(__int128 a = 0, __int128 b = 0, __int128 c = 0) : a(a), b(b), c(c) {}
    Line(Point a1, Point a2) {
        a = a2.x - a1.x;
        b = a1.y - a2.y;
        c = (__int128)a1.x * a2.y - (__int128)a1.y * a2.x;
    }
};

Point mn = Point(1e9 + 1, 1e9 + 1);

bool cmp1(Point a, Point b) {
    Vector v1 = Vector(mn, a), v2 = Vector(mn, b);
    if (v1 * v2 == 0) {
        return v1.get() < v2.get();
    }
    return v1 * v2 > 0;
}

bool cmp2(Vector a, Vector b) {
    if (a * b == 0) {
        return a.get() < b.get();
    }
    return a * b > 0;
}

bool rch(Point p1, Point p2, vector<Point> & a, vector<Vector> & k) {
    Line ch1 = Line(p1, p2);
    Vector v1 = Vector(p1, p2), v2 = Vector(p2, p1);
    int i = lower_bound(k.begin(), k.end(), v1, cmp2) - k.begin();
    int i2 = lower_bound(k.begin(), k.end(), v2, cmp2) - k.begin();
    i %= (int)a.size();
    i2 %= (int)a.size();
    //cout << "! " << i << " " << i2 << endl;
    Line ch2 = Line(a[i], Point(a[i].x + v1.x, a[i].y + v1.y));
    Line ch3 = Line(a[i2], Point(a[i2].x + v1.x, a[i2].y + v1.y));
    //cout << "? " << ch2.c << " " << ch3.c << endl;
    return !((ch3.c <= ch1.c && ch1.c <= ch2.c) || (ch2.c <= ch1.c && ch1.c <= ch3.c));
}

bool in_angle(Point a, Point o, Point b, Point p) {
    Vector v1 = Vector(o, a), v2 = Vector(o, b), v3 = Vector(o, p);
    if (v1 * v2 == 0) {
        return 0;
    }
    ll x1 = v1 * v2, x2 = v1 * v3, x3 = v2 * v1, x4 = v2 * v3;
    return ((x1 <= 0 && x2 <= 0) || (x1 >= 0 && x2 >= 0)) && ((x3 <= 0 && x4 <= 0) || (x3 >= 0 && x4 >= 0));
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int m;
    cin >> m;
    vector<Point> b(m);
    int in = -1;
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        if (b[i].y < mn.y || (b[i].y == mn.y && b[i].x < mn.x)) {
            mn = b[i];
            in = i;
        }
    }
    assert(n <= 300 || m >= 10);
    b.erase(b.begin() + in);
    sort(b.begin(), b.end(), cmp1);
    vector<Point> st;
    st.push_back(mn);
    st.push_back(b[0]);
    for (int i = 1; i < max(1, m - 1); ++i) {
        while ((int)st.size() >= 2 && Vector(st[(int)st.size() - 2], st.back()) * Vector(st.back(), b[i]) <= 0) {
            st.pop_back();
        }
        st.push_back(b[i]);
    }
    b = st;
    vector<Vector> to_ch;
    for (int i = 0; i < (int)b.size(); ++i) {
        int j = (i + 1) % (int)b.size();
        to_ch.push_back(Vector(b[i], b[j]));
        //cout << "{" << b[i].x << ", " << b[i].y << "} ";
    }
    //cout << endl;
    int r = 1;
    ll now = 0;
    ll ans = 0;
    for (int l = 0; l < n; ++l) {
        if (l != 0) {
            now -= abs(Vector(a[r], a[l]) * Vector(a[r], a[l - 1]));
        }
        if ((int)b.size() == 1) {
            while (!(in_angle(a[r], a[l], a[(r + 1) % n], b[0]))) {
                now += abs(Vector(a[l], a[r]) * Vector(a[l], a[(r + 1) % n]));
                r++;
                r %= n;
            }
        } else if ((int)b.size() == 2) {
            while (!(in_angle(a[r], a[l], a[(r + 1) % n], b[1])) && !(in_angle(a[r], a[l], a[(r + 1) % n], b[0]))) {
                now += abs(Vector(a[l], a[r]) * Vector(a[l], a[(r + 1) % n]));
                r++;
                r %= n;
            }
        } else {
            while (rch(a[l], a[(r + 1) % n], b, to_ch) && !(in_angle(a[r], a[l], a[(r + 1) % n], b[0]))) {
                now += abs(Vector(a[l], a[r]) * Vector(a[l], a[(r + 1) % n]));
                r++;
                r %= n;
            }
        }
        //cout << l << " " << r << endl;
        ans = max(now, ans);
    }
    cout << ans << endl;
    return 0;
}
