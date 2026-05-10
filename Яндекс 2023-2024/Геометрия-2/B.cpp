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
    return a.x * b.y - b.x * a.y;
}

ll operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

bool ch3(Point a, Point o, Point b, Point p) {
    if (p == o) return 1;
    Vector v1 = Vector(o, a), v2 = Vector(o, b), v3 = Vector(o, p);
    ll x1 = v1 * v2, x2 = v1 * v3, x3 = v2 * v1, x4 = v2 * v3;
    return ((x1 <= 0 && x2 <= 0) || (x1 >= 0 && x2 >= 0)) && ((x3 <= 0 && x4 <= 0) || (x3 >= 0 && x4 >= 0));
}

bool ch2(Point a, Point b, Point c, Point p) {
    return ch3(a, b, c, p) && ch3(b, a, c, p) && ch3(a, c, b, p);
}

bool ch(vector<Point> & a, Point p) {
    int n = (int)a.size();
    Vector v1 = Vector(a[0], p);
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        Vector v2 = Vector(a[0], a[m]);
        if (v2 * v1 <= 0) {
            r = m;
        } else {
            l = m;
        }
    }
    //cout << "! " << r << endl;
    if (r == n) {
        return false;
    }
    if (r == 1) {
        if (p == a[0] || p == a[1]) {
            return 1;
        }
        Vector v2 = Vector(a[1], p);
        return v1 * v2 == 0 && (v1 ^ v2) < 0;
    }
    return ch2(a[l], a[r], a[0], p);
}

signed main() {
    int n;
    cin >> n;
    vector<vector<Point>> a(n);
    vector<pair<ll, int>> b(n);
    vector<ll> s(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            Point p;
            cin >> p;
            a[i].push_back(p);
        }
        ll now = 0;
        for (int j = 0; j < k; ++j) {
            int j2 = (j + 1) % k;
            now += (a[i][j].x + a[i][j2].x) * (a[i][j].y - a[i][j2].y);
        }
        now = abs(now);
        b[i] = {now, i};
    }
    sort(b.begin(), b.end());
    s[0] = b[0].first;
    for (int i = 1; i < n; ++i) {
        s[i] = b[i].first - b[i - 1].first;
    }
    int q;
    cin >> q;
    ll ans = 0;
    vector<int> ch2(n);
    for (int i = 0; i < q; ++i) {
        Point p;
        cin >> p;
        int l = -1, r = n;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            if (ch(a[b[m].second], p)) {
                r = m;
            } else {
                l = m;
            }
        }
        //cout << r << endl;
        if (r != n) {
            ch2[r] = 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        if (ch2[i]) {
            ans += s[i];
        }
    }
    cout << ans / 2 << ".";
    if (ans % 2 == 1) {
        cout << "500000" << endl;
    } else {
        cout << "000000" << endl;
    }
    return 0;
}
