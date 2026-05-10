#include<bits/stdc++.h>

#define int long long

using namespace std;
using ld = long double;

const int INF = 5e18;

struct Point {
    ld x, y;
    Point(ld x = 0, ld y = 0) : x(x), y(y) {}
};

bool operator < (Point a, Point b) {
    if (a.x < b.x) return 1;
    if (a.x > b.x) return 0;
    return a.y < b.y;
}

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

ld operator % (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

struct Line {
    ld a, b, c;
    Line(ld a = 0, ld b = 0, ld c = 0) : a(a), b(b), c(c) {}
    Line(Point b0, Point b1) {
        //cout << b0.x << " " << b0.y << " " << b1.x << " " << b1.y << endl;
        a = b0.y - b1.y;
        b = b1.x - b0.x;
        c = b0.y * b1.x - b0.x * b1.y;
    }
};

Point mn;

bool cmp(Point a, Point b) {
    Vector v1 = Vector(mn, a);
    Vector v2 = Vector(mn, b);
    return v1 * v2 > 0;
}

ld get_sum(int l, int r, vector<Point> & all, vector<ld> & pref) {
    if (l <= r) {
        return pref[r] - pref[l] + (all[r].x - all[l].x) * (all[l].y + all[r].y) / 2;
    }
    return pref[r] + pref.back() - pref[l] + (all[r].x - all[l].x) * (all[l].y + all[r].y) / 2;
}

int sgn(ld a) {
    if (a < 0) return -1;
    if (a == 0) return 0;
    return 1;
}

bool in_angle(Point a, Point o, Point b, Point p) {
    Vector v1 = Vector(o, a), v2 = Vector(o, b), v3 = Vector(o, p);
    int y1 = sgn(v1 * v2), y2 = sgn(v1 * v3), y3 = sgn(v2 * v1), y4 = sgn(v2 * v3);
    //cout << y1 << " " << y2 << " " << y3 << " " << y4 << endl;
    if (y1 == 0) {
        if (y2 == 0) return v1 % v2 >= 0;
        return 0;
    }
    return y1 * y2 >= 0 && y3 * y4 >= 0;
}

bool ch_in(vector<Point> & all, Point p) {
    if (!in_angle(all[1], all[0], all.back(), p)) return 0;
    int l = 1, r = (int)all.size() - 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        Vector v1 = Vector(all[0], all[m]);
        Vector v2 = Vector(all[0], p);
        if (v1 * v2 > 0) {
            l = m;
        } else {
            r = m;
        }
    }
    return in_angle(all[l], all[r], all[0], p) && in_angle(all[r], all[l], all[0], p);
}

const int LN = 11;
mt19937 rnd(57);

bool cmp0(Vector a, Vector b) {
    if (a * b == 0) {
        return a.x * a.x + a.y * a.y > b.x * b.x + b.y * b.y;
    }
    return a * b < 0;
}

bool cmp1(Vector a, Vector b) {
    if (a * b == 0) {
        return a.x * a.x + a.y * a.y > b.x * b.x + b.y * b.y;
    }
    return a * b > 0;
}

pair<int, int> get_c(Point p, vector<Point> & all) {
    int n = (int)all.size();
    int d = rnd() % n;
    for (int i = LN - 1; i >= 0; --i) {
        int d1 = (d + (1 << i)) % n;
        int d2 = ((d - (1 << i)) % n + n) % n;
        if (cmp0(Vector(p, all[d]), Vector(p, all[d1]))) {
            d = d1;
        }
        if (cmp0(Vector(p, all[d]), Vector(p, all[d2]))) {
            d = d2;
        }
    }
    //cout << d << endl;
    int u = rnd() % n;
    //cout << u << endl;
    for (int i = LN - 1; i >= 0; --i) {
        int u1 = (u + (1 << i)) % n;
        int u2 = ((u - (1 << i)) % n + n) % n;
        if (cmp1(Vector(p, all[u]), Vector(p, all[u1]))) {
            u = u1;
        }
        if (cmp1(Vector(p, all[u]), Vector(p, all[u2]))) {
            u = u2;
        }
    }
    return {u, d};
}

ld dif(Point p, vector<Point> & all, vector<ld> & pref) {
    if (ch_in(all, p)) return -INF;
    auto [ls, rs] = get_c(p, all);
    return abs(Vector(p, all[ls]) * Vector(p, all[rs])) / 2 - get_sum(ls, rs, all, pref);
}

pair<Point, Point> intersect(Line now, int r) {
    ld dwn = now.a * now.a + now.b * now.b;
    if (now.c * now.c / dwn > r * r) return {Point(0, 0), Point(0, 0)};
    ld x0 = -now.a * now.c / dwn;
    ld y0 = -now.b * now.c / dwn;
    ld dist = sqrtl(r * r - now.c * now.c / dwn);
    ld add = dist / sqrtl(dwn);
    Point a = Point(x0 + now.b * add, y0 - now.a * add);
    Point b = Point(x0 - now.b * add, y0 + now.a * add);
    return {a, b};
}

vector<Point> cht(vector<Point> all) {
    sort(all.begin(), all.end());
    mn = all[0];
    all.erase(all.begin());
    sort(all.begin(), all.end(), cmp);
    vector<Point> ans;
    ans.push_back(mn);
    ans.push_back(all[0]);
    for (int i = 1; i < (int)all.size(); ++i) {
        while ((int)ans.size() > 2 && Vector(ans[(int)ans.size() - 2], ans.back()) * Vector(ans.back(), all[i]) < 0) {
            ans.pop_back();
        }
        ans.push_back(all[i]);
    }
    return ans;
}

int wh(Vector a) {
    return (a.y > 0 || a.y == 0 && a.x > 0);
}

bool cmp2(Point a0, Point b0) {
    Vector a = Vector(a0.x, a0.y);
    Vector b = Vector(b0.x, b0.y);
    int wha = wh(a), whb = wh(b);
    if (wha == whb) return cmp1(a, b);
    return wha > whb;
}

const ld EPS = INF;

ld f(vector<Point> all, Point p, int r, int ch) {
    all = cht(all);
    //cout << (int)all.size() << endl;
    for (auto & now : all) {
        //cout << now.x << " " << now.y << endl;
        now.x -= p.x;
        now.y -= p.y;
        //cout << now.x << " " << now.y << endl;
    }
    p.x = 0;
    p.y = 0;
    ld s = 0;
    vector<ld> pref((int)all.size() + 1);
    for (int i = 0; i < (int)all.size(); ++i) {
        int j = (i + 1) % (int)all.size();
        s += (all[i].x - all[j].x) * (all[i].y + all[j].y) / 2;
        pref[i + 1] = s;
    }
    vector<Point> tr;
    for (int i = 0; i < (int)all.size(); ++i) {
        int j = (i + 1) % (int)all.size();
        Line now = Line(all[i], all[j]);
        pair<Point, Point> u = intersect(now, r);
        tr.push_back(u.first);
        tr.push_back(u.second);
    }
    sort(tr.begin(), tr.end(), cmp2);
    int k = (int)tr.size();
    vector<pair<Point, int>> ntr;
    for (int i = 0; i < k; ++i) {
        int j = (i + 1) % k;
        Point now = Point((tr[i].x + tr[j].x) / 2, (tr[i].y + tr[j].y) / 2);
        ld dwn = sqrtl(now.x * now.x + now.y * now.y);
        if (dwn == 0) {
            now = Point(tr[j].y - tr[i].y, -(tr[j].x - tr[i].x));
            dwn = sqrtl(now.x * now.x + now.y * now.y);
        }
        now.x = (now.x * r / dwn);
        now.y = (now.y * r / dwn);
        int fl = 0;
        if (abs(tr[i].x - tr[j].x) < EPS && abs(tr[i].y - tr[j].y) < EPS) fl = 1;
        ntr.push_back({now, fl});
        if (tr[i].x * tr[j].y - tr[j].x * tr[i].y >= 0) ntr.push_back({Point(-now.x, -now.y), fl});
    }
    vector<Point> rtr;
    vector<pair<int, int>> nowch;
    for (auto [p1, fl] : ntr) {
        if (!ch_in(all, p1)) {
            auto [ni, nj] = get_c(p1, all);
            for (int di = -fl; di <= 0; ++di) {
                for (int dj = 0; dj <= fl; ++dj) {
                    int i = (di + ni + (int)all.size()) % (int)all.size();
                    int j = (dj + nj + (int)all.size()) % (int)all.size();
                    nowch.push_back({i, j});
                }
            }
        }
    }
    sort(nowch.begin(), nowch.end());
    nowch.erase(unique(nowch.begin(), nowch.end()), nowch.end());
    for (auto [i, j] : nowch) {
        Line now = Line(all[i], all[j]);
        ld dwn = sqrtl(now.a * now.a + now.b * now.b);
        rtr.push_back(Point(now.a * r / dwn, now.b * r / dwn));
        rtr.push_back(Point(-now.a * r / dwn, -now.b * r / dwn));
    }
    ld rans = s;
    for (auto p1 : rtr) {
        //cout << p1.x << " " << p1.y << endl;
        //cout << all[0].x << " " << all[0].y << " " << all[1].x << " " << all[1].y << endl;
        ld rdif = dif(p1, all, pref);
        //cout << p1.x << " " << p1.y << " " << rdif << endl;
        rans = max(rans, s + rdif);
    }
    return rans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n, r;
        cin >> n >> r;
        vector<Point> all(n);
        vector<int> tp(n);
        for (int i = 0; i < n; ++i) {
            cin >> all[i].x >> all[i].y;
            cin >> tp[i];
        }
        vector<Point> now = cht(all);
        ld ans = 0;
        for (int i = 0; i < (int)now.size(); ++i) {
            int j = (i + 1) % (int)now.size();
            ans += (now[i].x - now[j].x) * (now[i].y + now[j].y) / 2;
        }
        for (int i = 0; i < n; ++i) {
            if (tp[i] == 2) continue;
            vector<Point> nall;
            for (int j = 0; j < n; ++j) {
                if (j != i) {
                    nall.push_back(all[j]);
                }
            }
            ans = max(ans, f(nall, all[i], r, n));
        }
        //cout << ans << endl;
        cout << setprecision(100) << ans << endl;
    }
    return 0;
}

/*
1
3 1
0 0 1
1 0 2
0 1 2
*/
