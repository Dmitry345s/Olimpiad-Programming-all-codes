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

ostream& operator << (ostream& in, Point& a) {
    in << a.x << " " << a.y;
    return in;
}

int operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    int a, b, c;
    Line (Point x, Point y) {
        a = y.y - x.y;
        b = x.x - y.x;
        c = x.y * y.x - y.y * x.x;
    }
};

int get (Vector a) {
    return a.x * a.x + a.y * a.y;
}

Point mn;

bool cmp(Point a, Point b) {
    Vector v1 = Vector(a, mn);
    Vector v2 = Vector(b, mn);
    if (v1 * v2 == 0) {
        return get(v1) < get(v2);
    }
    return v1 * v2 > 0;
}

int tr (int a, int b) {
    return (a > 0 && b > 0) || (a < 0 && b < 0);
}

bool in_angle(Point a, Point o, Point b, Point p) {
    Vector v1 = Vector(a, o), v2 = Vector(b, o), v3 = Vector(p, o);
    if (v1 * v3 == 0 || v2 * v3 == 0) {
        return false;
    }
    return tr((v1 * v3), (v1 * v2)) && tr((v2 * v3), (v2 * v1));
}

signed main() {
    int n, m;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cin >> m;
    vector<Point> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        mn = a[i];
        sort(b.begin(), b.end(), cmp);
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            if (!in_angle(b[0], a[i], b[m - 1], a[j])) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    vector<int> d(n, 1e9);
    d[0] = 0;
    queue<int> q;
    q.push(0);
    vector<int> used(n);
    used[0] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (d[v] + 1 < d[to]) {
                d[to] = d[v] + 1;
                q.push(to);
            }
        }
    }
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (d[i] <= 2) {
            //cout << i << endl;
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
