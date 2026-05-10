#include<bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

bool operator== (Point a, Point b) {
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

long long operator* (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

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

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
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
        while ((int)all.size() > 1 && cmp3(Vector(all.back(), a[i]), Vector(all[(int)all.size() - 2], all.back()), Vector(all[(int)all.size() - 2], all.back()))) {
            all.pop_back();
        }
        all.push_back(a[i]);
    }
    Point st = all[(min_element(all.begin(), all.end(), cmp) - all.begin())];
    Point st2 = all[(max_element(all.begin(), all.end(), cmp) - all.begin())];
    st2.x *= -1;
    st2.y *= -1;
    Point rst;
    rst.x = st.x + st2.x;
    rst.y = st.y + st2.y;
    vector<Vector> lines;
    for (int i = 0; i < (int)all.size(); ++i) {
        //cout << all[i].x << " " << all[i].y << endl;
        int j = (i + 1) % (int)all.size();
        lines.push_back(Vector(all[i], all[j]));
        lines.push_back(Vector(all[j], all[i]));
    }
    sort(lines.begin(), lines.end(), cmp4);
    vector<Point> last((int)lines.size() + 1);
    last[0] = rst;
    //cout << rst.x << " " << rst.y << endl;
    long long dist = Vector(Point(), last[0]).get();
    for (int i = 0; i < (int)lines.size(); ++i) {
        //cout << "! " << lines[i].x << " " << lines[i].y << endl;
        last[i + 1] = Point(last[i].x + lines[i].x, last[i].y + lines[i].y);
        //cout << last[i + 1].x << " " << last[i + 1].y << endl;
        dist = max(dist, Vector(Point(), last[i + 1]).get());
    }
    cout << dist << endl;
    return 0;
}
