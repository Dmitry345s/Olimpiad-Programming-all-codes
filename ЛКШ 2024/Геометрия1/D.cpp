#include<bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

long long operator== (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

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

long long operator^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

long long operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

struct Line {
    long long a, b, c;
    Line(long long a = 0, long long b = 0, long long c = 0) : a(a), b(b), c(c) {};
    long long dist(Point u) {
        return a * u.x + b * u.y + c;
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
    if ((a.y < 0 || (a.y == 0 && a.x < 0)) && (b.y > 0 || (b.y == 0 && b.x >= 0))) {
        return 0;
    }
    if ((b.y < 0 || (b.y == 0 && b.x < 0)) && (a.y > 0 || (a.y == 0 && a.x >= 0))) {
        return 1;
    }
    return a * b > 0;
}

int get(vector<Vector> & to_ans, Vector a) {
    return (lower_bound(to_ans.begin(), to_ans.end(), a, cmp4) - to_ans.begin()) % (int)to_ans.size();
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<Line> lines(n);
    for (int i = 0; i < n; ++i) {
        cin >> lines[i].a >> lines[i].b >> lines[i].c;
        //swap(lines[i].a, lines[i].b);
    }
    vector<Point> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    if (m == 1) {
        vector<int> ans;
        for (int i = 0; i < n; ++i) {
            if (lines[i].dist(a[0]) == 0) {
                ans.push_back(i);
            }
        }
        cout << (int)ans.size() << endl;
        for (int i = 0; i < (int)ans.size(); ++i) {
            cout << ans[i] + 1 << " ";
        }
        return 0;
    }
    sort(a.begin(), a.end(), cmp);
    a.erase(unique(a.begin(), a.end()), a.end());
    mn = a[0];
    a.erase(a.begin());
    sort(a.begin(), a.end(), cmp2);
    vector<Point> all;
    all.push_back(mn);
    all.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
        while ((int)all.size() > 1 && cmp3(Vector(all.back(), a[i]), Vector(all[(int)all.size() - 2], all.back()), Vector(all[(int)all.size() - 2], a[i]))) {
            all.pop_back();
        }
        all.push_back(a[i]);
    }
    vector<Vector> to_ans;
    for (int i = 0; i < (int)all.size(); ++i) {
        //cout << all[i].x << " " << all[i].y << endl;
        int j = (i + 1) % (int)all.size();
        to_ans.push_back(Vector(all[i], all[j]));
        //cout << to_ans[i].x << " " << to_ans[i].y << endl;
    }
    //sort(to_ans.begin(), to_ans.end(), cmp4);
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        int j = get(to_ans, Vector(lines[i].b, -lines[i].a));
        int j2 = get(to_ans, Vector(-lines[i].b, lines[i].a));
        //cout << j << " " << j2 << endl;
        long long d1 = lines[i].dist(all[j]), d2 = lines[i].dist(all[j2]);
        if (d1 <= 0 && d2 >= 0 || d1 >= 0 && d2 <= 0) {
            ans.push_back(i);
        }
    }
    cout << (int)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}
