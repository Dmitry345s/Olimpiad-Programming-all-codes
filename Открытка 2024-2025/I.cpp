#pragma GCC optimize("O3","unroll-loops")
#include<bits/stdc++.h>

//#define int long long

using namespace std;
mt19937 rnd(179);

using ll = long long;
using ld = long double;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

istream& operator>> (istream& in, Point& a) {
    in >> a.x >> a.y;
    return in;
}

bool operator< (Point a, Point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

bool operator== (Point a, Point b) {
    return (a.x == b.x && a.y == b.y);
}

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    ll get() {
        return 1ll * x * x + 1ll * y * y;
    }
};

istream& operator>> (istream& in, Vector& a) {
    in >> a.x >> a.y;
    return in;
}

ll operator* (Vector a, Vector b) {
    return 1ll * a.x * b.y - 1ll * b.x * a.y;
}

ll operator% (Vector a, Vector b) {
    return 1ll * a.x * b.x + 1ll * a.y * b.y;
}

const int INF = 2e9;
Point mn;

bool cmp(Point a, Point b) {
    Vector a2 = Vector(mn, a), b2 = Vector(mn, b);
    if (a2 * b2 == 0) {
        return a2.get() < b2.get();
    }
    return a2 * b2 > 0;
}

bool cmp3(Point a, Point b, Point c) {
    Vector v1 = Vector(a, b);
    Vector v2 = Vector(b, c);
    if (v1 * v2 == 0) {
        return Vector(a, c).get() <= v1.get();
    }
    return v1 * v2 < 0;
}

vector<Point> hull(vector<Point>& a) {
    if ((int)a.size() == 0) return {};
    auto it = min_element(a.begin(), a.end());
    mn = *it;
    a.erase(it);
    sort(a.begin(), a.end(), cmp);
    a.erase(unique(a.begin(), a.end()), a.end());
    if ((int)a.size() != 0 && a[0] == mn) a.erase(a.begin());
    if ((int)a.size() == 0) {
        return {mn};
    }
    vector<Point> st;
    st.push_back(mn);
    st.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
        while ((int)st.size() >= 2 && cmp3(st[(int)st.size() - 2], st.back(), a[i])) {
            st.pop_back();
        }
        st.push_back(a[i]);
    }
    return st;
}

int whr(Vector a) {
    return !(a.y > 0 || (a.y == 0 && a.x >= 0));
}

bool cmp4(Vector a, Vector b) {
    if (whr(a) == whr(b)) {
        return a * b > 0;
    }
    return whr(a) < whr(b);
}

ll dist(vector<Point>& a, vector<Point> b) {
    for (int i = 0; i < (int)b.size(); ++i) {
        b[i].x *= -1;
        b[i].y *= -1;
    }
    //reverse(b.begin(), b.end());
    int j = min_element(b.begin(), b.end()) - b.begin();
    vector<Point> rb;
    for (int i = 0; i < (int)b.size(); ++i) {
        int x = (i + j) % (int)b.size();
        rb.push_back(b[x]);
    }
    b = rb;
    Point st = Point(b[0].x + a[0].x, b[0].y + a[0].y);
    vector<Point> all;
    all.push_back(st);
    vector<Vector> aa, bb;
    for (int i = 0; i < (int)a.size(); ++i) {
        aa.push_back(Vector(a[i], a[(i + 1) % (int)a.size()]));
    }
    for (int i = 0; i < (int)b.size(); ++i) {
        bb.push_back(Vector(b[i], b[(i + 1) % (int)b.size()]));
    }
    int r = 0;
    for (int l = 0; l < (int)aa.size(); ++l) {
        while (r < (int)bb.size() && (whr(bb[r]) < whr(aa[l]) || aa[l] * bb[r] < 0)) {
            all.push_back(Point(all.back().x + bb[r].x, all.back().y + bb[r].y));
            r++;
        }
        all.push_back(Point(all.back().x + aa[l].x, all.back().y + aa[l].y));
    }
    for (int i = r; i < (int)bb.size(); ++i) {
        all.push_back(Point(all.back().x + bb[i].x, all.back().y + bb[i].y));
    }
    ll ans = 0;
    for (int i = 0; i < (int)all.size(); ++i) {
        ans = max(ans, 1ll * all[i].x * all[i].x + 1ll * all[i].y * all[i].y);
    }
    return ans;
}

/*ll rsolve(int l, int r, vector<vector<Point>>& now) {
    if (l + 1 == r) {
        return 0;
    }
    int m = (l + r) / 2;
    ll ans = max(rsolve(l, m, now), rsolve(m, r, now));
    vector<Point> a;
    vector<Point> b;
    for (int i = l; i < m; ++i) {
        for (Point ch : now[i]) {
            a.push_back(ch);
        }
    }
    for (int i = m; i < r; ++i) {
        for (Point ch : now[i]) {
            b.push_back(ch);
        }
    }
    if ((int)a.size() == 0 || (int)b.size() == 0) {
        return ans;
    }
    hull(a);
    hull(b);
    for (int i = l; i < m; ++i) {
        now[i].clear();
    }
    for (int i = m; i < r; ++i) {
        now[i].clear();
    }
    now[l] = a;
    now[m] = b;
    ans = max(ans, dist(a, b));
    return ans;
}*/

vector<Point> merg(vector<Point>& a, vector<Point>& b) {
    vector<Point> ans;
    int r = 0;
    for (int l = 0; l < (int)a.size(); ++l) {
        while (r < (int)b.size() && cmp(b[r], a[l])) {
            ans.push_back(b[r]);
            r++;
        }
        ans.push_back(a[l]);
    }
    for(int i = r; i < (int)b.size(); ++i) {
        ans.push_back(b[i]);
    }
    return ans;
}

const int LN = 19;

int get(vector<Point>& a) {
    int n = (int)a.size();
    int now = 0;
    for (int i = 0; i < n; ++i) {
        if (cmp(a[i], a[now])) {
            now = i;
        }
    }
    return now;
}

vector<Point> mhull(vector<Point>& a, vector<Point>& b) {
    if ((int)a.size() == 0) return b;
    if ((int)b.size() == 0) return a;
    if (b[0] < a[0]) {
        swap(a, b);
    }
    mn = a[0];
    int l = get(b);
    vector<Point> now;
    int i1 = l, i2 = (l + 1) % (int)b.size();
    while (i1 != i2) {
        if (cmp(b[i1], b[i2])) {
            now.push_back(b[i1]);
            i1 = (i1 - 1 + (int)b.size()) % (int)b.size();
        } else {
            now.push_back(b[i2]);
            i2 = (i2 + 1) % (int)b.size();
        }
    }
    now.push_back(b[i1]);
    //vector<Point> now = merg(f, s);
    a.erase(a.begin());
    a = merg(a, now);
    a.erase(unique(a.begin(), a.end()), a.end());
    if ((int)a.size() != 0 && a[0] == mn) a.erase(a.begin());
    if ((int)a.size() == 0) {
        return {mn};
    }
    vector<Point> st;
    st.push_back(mn);
    st.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
        while ((int)st.size() >= 2 && cmp3(st[(int)st.size() - 2], st.back(), a[i])) {
            st.pop_back();
        }
        st.push_back(a[i]);
    }
    return st;
}

pair<vector<Point>, ll> rsolve(int l, int r, vector<vector<Point>>& now) {
    if (l + 1 == r) {
        return {hull(now[l]), 0};
    }
    int m = (l + r) / 2;
    auto [a, x] = rsolve(l, m, now);
    auto [b, y] = rsolve(m, r, now);
    ll ans = max(x, y);
    if ((int)a.size() != 0 && (int)b.size() != 0) {
        ans = max(ans, dist(a, b));
    }
    return {mhull(a, b), ans};
}

ll solve(vector<vector<pair<Point, Vector>>>& all, int n, int t) {
    vector<vector<Point>> now(n);
    for (int i = 0; i < n; ++i) {
        for (auto [p, v] : all[i]) {
            p.x += v.x * t;
            p.y += v.y * t;
            now[i].push_back(p);
        }
    }
    return rsolve(0, n, now).second;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    //cout << LONG_LONG_MAX << endl;
    cout.precision(20);
    cout << fixed;
    while (_--) {
        int n, t;
        cin >> n >> t;
        vector<vector<pair<Point, Vector>>> all(n);
        for (int i = 0; i < n; ++i) {
            Point a;
            Vector b;
            int c;
            cin >> a;
            cin >> b;
            cin >> c;
            --c;
            all[c].push_back({a, b});
        }
        //shuffle(all.begin(), all.end(), rnd);
        //shuffle(all.begin(), all.end(), rnd);
        //shuffle(all.begin(), all.end(), rnd);
        ll ans = solve(all, n, t);
        int l = -1, r = t;
        while (l + 2 < r) {
            int m = (l + r) / 2;
            ll x = solve(all, n, m);
            ll y = solve(all, n, m + 1);
            ans = min(ans, min(x, y));
            if (x < y) {
                r = m + 1;
            } else {
                l = m;
            }
            //cout << l << " " << r << endl;
        }
        ans = min(ans, solve(all, n, l + 1));
        cout << sqrtl(ans) << '\n';
    }
    return 0;
}
