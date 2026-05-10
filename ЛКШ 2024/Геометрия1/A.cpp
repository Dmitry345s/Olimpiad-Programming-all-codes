#include<bits/stdc++.h>

using namespace std;

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

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

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

long long operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

long long operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

Point mn;

bool cmp(Point a, Point b) {
    Vector a2 = Vector(mn, a), b2 = Vector(mn, b);
    if (a2 * b2 == 0) {
        return a2.get() < b2.get();
    }
    return a2 * b2 > 0;
}

bool cmp3(Vector a, Vector b, Vector c) {
    if (a * b == 0) {
        return c.get() > b.get();
    }
    return a * b > 0;
}

bool cmp2(Point a, Point b) {
    if (a.y == b.y) {
        return a.x < b.x;
    }
    return a.y < b.y;
}

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
    }
    sort(a.begin(), a.end(), cmp2);
    //cout << (int)a.size() << endl;
    a.erase(unique(a.begin(), a.end()), a.end());
    //cout << (int)a.size() << endl;
    mn = a[0];
    a.erase(a.begin());
    sort(a.begin(), a.end(), cmp);
    vector<Point> st;
    st.push_back(mn);
    st.push_back(a[0]);
    for (int i = 1; i < (int)a.size(); ++i) {
        //cout << a[i].x << " " << a[i].y << endl;
        while ((int)st.size() > 1 && cmp3(Vector(st.back(), a[i]), Vector(st[(int)st.size() - 2], st.back()), Vector(st[(int)st.size() - 2], a[i]))) {
            st.pop_back();
        }
        st.push_back(a[i]);
    }
    long long s = 0;
    for (int i = 0; i < (int)st.size(); ++i) {
        int j = (i + 1) % (int)st.size();
        s += (st[i].x - st[j].x) * (st[i].y + st[j].y);
    }
    cout << (int)st.size() << endl;
    for (int i = 0; i < (int)st.size(); ++i) {
        cout << st[i].x << " " << st[i].y << endl;
    }
    cout << s / 2;
    if (s % 2) {
        cout << ".5" << endl;
    } else {
        cout << ".0" << endl;
    }
    return 0;
}
