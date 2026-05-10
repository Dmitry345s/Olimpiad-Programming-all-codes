#include<bits/stdc++.h>

#define int long long
#define double long double
using namespace std;

struct Point {
    int x, y;
    Point (int x1 = 0, int y1 = 0) {
        x = x1;
        y = y1;
    }
};

istream& operator >> (istream& in, Point& a) {
    in >> a.x >> a.y;
    return in;
}

struct Line {
    int a, b, c;
    Line (Point x, Point y) {
        a = y.y - x.y;
        b = x.x - y.x;
        c = x.y * y.x - y.y * x.x;
    }
};

double get (Line a, int x) {
    return -(a.a * x + a.c) / (double) a.b;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<Point> a(n), b(m);
    vector<pair<int, int>> xs;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        xs.push_back({a[i].x, i});
    }
    for (int j = 0; j < m; ++j) {
        cin >> b[j];
        xs.push_back({b[j].x, j + n});
    }
    sort(xs.begin(), xs.end());
    int lind = 0, lind2 = 0;
    vector<double> del(n), del2(m);
    double minm = 1e9;
    for (int i = 0; i < xs.size() - 1; ++i) {
        if (xs[i].second < n) {
            Line now = Line(b[lind2], b[lind2 + 1]);
            del[xs[i].second] = abs(get(now, a[xs[i].second].x) - a[xs[i].second].y);
            minm = min(minm, del[xs[i].second]);
            lind = xs[i].second;
        } else {
            Line now = Line(a[lind], a[lind + 1]);
            del2[xs[i].second - n] = abs(get(now, b[xs[i].second - n].x) - b[xs[i].second - n].y);
            minm = min(minm, del2[xs[i].second - n]);
            lind2 = xs[i].second - n;
        }
    }
    del2.back() = del.back();
    int ans = 0;
    for (int i = 0; i < xs.size() - 1; ++i) {
        if (xs[i].second < n) {
            if (del[xs[i].second] == minm) {
                if (xs[i + 1].second < n) {
                    if (del[xs[i + 1].second] != minm) {
                        ans++;
                    }
                } else {
                    if (del2[xs[i + 1].second - n] != minm) {
                        ans++;
                    }
                }
            }
        } else {
            if (del2[xs[i].second - n] == minm) {
                if (xs[i + 1].second < n) {
                    if (del[xs[i + 1].second] != minm) {
                        ans++;
                    }
                } else {
                    if (del2[xs[i + 1].second - n] != minm) {
                        ans++;
                    }
                }
            }
        }
    }
    if (del[0] != minm) {
        ans++;
    }
    cout << ans << endl;
    /*int l = 0, l2 = 0;
    while (l < n && l2 < m) {
        if (a[l].x == b[l2].x) {
            del[l] = a[l].y - b[l2].y;
            del2[l2] - del[l];
            minm = min(minm, del[l]);
            if (l != n - 1) {
                if (a[l + 1].x < b[l2 + 1].x) {
                    l++;
                } else {
                    l2++;
                }
            } else {
                l2++;
            }
            continue;
        }
        if (a[l].x < b[l2].x) {
            Line now = Line(a[l], a[l + 1]);
            del2[l2] = abs(get(now, b[l2].x) - b[l2].y);
            minm = min(minm, del2[l2]);
        }
    }*/
    return 0;
}
