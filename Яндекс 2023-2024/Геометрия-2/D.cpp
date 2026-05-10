#include<bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
};

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

bool operator < (Point a, Point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
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

Point mn;

bool cmp(Point a, Point b) {
    Vector v1 = Vector(mn, a), v2 = Vector(mn, b);
    if (v1 * v2 == 0) {
        return v1.get() < v2.get();
    }
    return v1 * v2 < 0;
}

vector<Point> hull(vector<Point> a) {
    sort(a.begin(), a.end());
    mn = a[0];
    a.erase(a.begin());
    sort(a.begin(), a.end(), cmp);
    vector<Point> st;
    st.push_back(mn);
    st.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
        while ((int)st.size() >= 2 && Vector(st.back(), a[i]) * Vector(st[(int)st.size() - 2], st.back()) <= 0) {
            st.pop_back();
        }
        st.push_back(a[i]);
    }
    return st;
}

signed main() {
    int n, l;
    cin >> n >> l;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<Point> h = hull(a);
    long double ans = 2 * M_PI * l;
    for (int i = 0; i < (int)h.size(); ++i) {
        int j = (i + 1) % (int)h.size();
        ans += sqrtl(Vector(h[i], h[j]).get());
    }
    cout << setprecision(20) << ans << endl;
    return 0;
}
