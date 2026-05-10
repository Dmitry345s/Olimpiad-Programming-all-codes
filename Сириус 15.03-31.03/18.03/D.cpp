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

struct Vector {
    int x, y;
    Vector (int x1 = 0, int y1 = 0) {
        x = x1;
        y = y1;
    }
    Vector (Point a, Point b) {
        x = a.x - b.x;
        y = a.y - b.y;
    }
};

istream& operator >> (istream& in, Vector& a) {
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

int get (Vector a) {
    return a.x * a.x + a.y * a.y;
}

int MAX = 1e6;
vector<int> tree(4 * MAX);

void update(int v, int l, int r, int id, int x) {
    if (l + 1 == r) {
        tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x);
    } else {
        update(2 * v + 1, m, r, id, x);
    }
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    return get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr);
}

signed main() {
    int k, n, q;
    cin >> k >> n >> q;
    vector<Vector> vs(k);
    Vector minm1, minm2;
    for (int i = 0; i < k; ++i) {
        cin >> vs[i];
        if (get(vs[i]) >= get(minm1)) {
            minm2 = minm1;
            minm1 = vs[i];
        } else if (get(vs[i]) >= get(minm2)) {
            minm2 = vs[i];
        }
    }
    vs[0] = minm1;
    vs[1] = minm2;
    vector<int> a(n);
    vector<Point> cs(n);
    vector<array<int, 5>> b;
    vector<int> c;
    for (int i = 0; i < n; ++i) {
        cin >> cs[i];
        cin >> a[i];
        cs[i] = Point(cs[i].x - cs[i].y, cs[i].x + cs[i].y);
        b.push_back({cs[i].y, 0, cs[i].x, i, 0});
        c.push_back(cs[i].x);
        //cout << cs[i].x << " " << cs[i].y << endl;
    }
    for (int i = 0; i < q; ++i) {
        Point now;
        int t;
        cin >> now >> t;
        now = Point(now.x - now.y, now.x + now.y);
        int ans = 0;
        int ys = abs(vs[1].x * vs[0].y - vs[1].y * vs[0].x) * t;
        int xs = abs(vs[0].x * vs[1].y - vs[0].y * vs[1].x) * t;
        b.push_back({now.y - ys, -1, now.x - xs, now.x + xs, i});
        b.push_back({now.y + ys, 1, now.x - xs, now.x + xs, i});
        //cout << now.y << " " << now.x << " " << xs << " " << ys << endl;
        c.push_back(now.x - xs);
        c.push_back(now.x + xs);
    }
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()));
    sort(b.begin(), b.end());
    vector<int> ans(q);
    for (int i = 0; i < b.size(); ++i) {
        if (b[i][1] == 0) {
            int r = lower_bound(c.begin(), c.end(), b[i][2]) - c.begin();
            update(1, 0, MAX, r, a[b[i][3]]);
        } else {
            int r1 = lower_bound(c.begin(), c.end(), b[i][2]) - c.begin();
            int r2 = lower_bound(c.begin(), c.end(), b[i][3]) - c.begin();
            ans[b[i][4]] += b[i][1] * get(1, 0, MAX, r1, r2 + 1);
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
