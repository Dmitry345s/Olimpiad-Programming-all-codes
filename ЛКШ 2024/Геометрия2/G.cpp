#include<bits/stdc++.h>

using namespace std;

struct Point {
    long double x, y;
    Point(long double x = 0, long double y = 0) : x(x), y(y) {};
};

bool operator== (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

struct Vector {
    long double x, y;
    Vector(long double x = 0, long double y = 0) : x(x), y(y) {};
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    long double get() {
        return x * x + y * y;
    }
};

long double operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    long double k, b;
    Line(long double k = 0, long double b = 0) : k(k), b(b) {};
    long double get(long double x) {
        return k * x + b;
    }
};

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

vector<long double> cht;
vector<Line> lines;
const long double INF = 6e36;

long double operator+ (Line a, Line b) {
    return (long double)(b.b - a.b) / (long double)(a.k - b.k);
}

void add(Line now) {
    //cout << "# " << now.k << " " << now.b << endl;
    if ((int)lines.size() == 0) {
        lines.push_back(now);
        cht.push_back(-INF);
        return;
    }
    while ((int)lines.size() >= 1 && now + lines.back() < cht.back()) {
        lines.pop_back();
        cht.pop_back();
    }
    cht.push_back(lines.back() + now);
    //cout << lines.back() + now << endl;
    lines.push_back(now);
}

long double get(long double x) {
    return lines[upper_bound(cht.begin(), cht.end(), x) - cht.begin() - 1].get(x);
}

signed main() {
    int t, _;
    cin >> t >> _;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<Point> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i].x >> a[i].y;
        }
        sort(a.begin(), a.end(), cmp);
        mn = a[0];
        a.erase(a.begin());
        sort(a.begin(), a.end(), cmp2);
        vector<Point> st;
        st.push_back(mn);
        st.push_back(a[0]);
        for (int i = 1; i < (int)a.size(); ++i) {
            //cout << "! " << a[i].x << " " << a[i].y << endl;
            while ((int)st.size() > 1 && cmp3(Vector(st.back(), a[i]), Vector(st[(int)st.size() - 2], st.back()), Vector(st[(int)st.size() - 2], a[i]))) {
                st.pop_back();
            }
            st.push_back(a[i]);
        }
        //cout << st.size() << endl;
        Point down = st[min_element(st.begin(), st.end(), cmp) - st.begin()];
        //cout << down.x << " " << down.y << endl;
        Point up = st[max_element(st.begin(), st.end(), cmp) - st.begin()];
        //cout << up.x << " " << up.y << endl;
        up.x *= -1;
        up.y *= -1;
        Point rst = Point(down.x + up.x, down.y + up.y);
        //cout << rst.x << " " << rst.y << endl;
        vector<Vector> all;
        for (int i = 0; i < (int)st.size(); ++i) {
            //cout << st[i].x << " " << st[i].y << endl;
            int j = (i + 1) % (int)st.size();
            all.push_back(Vector(st[i], st[j]));
            all.push_back(Vector(st[j], st[i]));
        }
        sort(all.begin(), all.end(), cmp4);
        vector<Point> b;
        b.push_back(rst);
        for (int i = 0; i < (int)all.size(); ++i) {
            //cout << all[i].x << " " << all[i].y << endl;
            b.push_back(Point(b.back().x + all[i].x, b.back().y + all[i].y));
            //cout << b.back().x << " " << b.back().y << endl;
        }
        b.pop_back();
        vector<pair<long double, long double>> to_ans;
        for (int i = 0; i < (int)b.size(); ++i) {
            //cout << "? " << b[i].x << " " << b[i].y << endl;
            to_ans.push_back({b[i].x * b[i].x, b[i].y * b[i].y});
        }
        //cout << 1 << endl;
        sort(to_ans.begin(), to_ans.end());
        to_ans.erase(unique(to_ans.begin(), to_ans.end()), to_ans.end());
        cht.clear();
        lines.clear();
        //cout << setprecision(100) << INF << endl;
        for (int i = 0; i < (int)to_ans.size(); ++i) {
            add(Line(to_ans[i].first, to_ans[i].second));
        }
        //cout << 1 << endl;
        for (int i = 0; i < q; ++i) {
            long double alpha;
            cin >> alpha;
            cout << setprecision(40) << sqrtl(get(alpha * alpha)) << endl;
        }
    }
    return 0;
}
