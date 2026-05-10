#include<bits/stdc++.h>

using namespace std;
using ll = long long;

struct Point {
    ll x, y;
    Point(ll x = 0, ll y = 0) : x(x), y(y) {}
};

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
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
    return a.x * b.y - a.y * b.x;
}

ll operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

Point mn = Point(2e9, 2e9);

bool cmp(pair<Point, int> a, pair<Point, int> b) {
    Vector v1 = Vector(mn, a.first), v2 = Vector(mn, b.first);
    if (v1 * v2 == 0) {
        return v1.get() > v2.get();
    }
    return v1 * v2 < 0;
}

signed main() {
    int n;
    cin >> n;
    int in = -1;
    vector<pair<Point, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
        if (a[i].first.y < mn.y || (a[i].first.y == mn.y && a[i].first.x < mn.x)) {
            mn = a[i].first;
            in = i;
        }
    }
    a.erase(a.begin() + in);
    sort(a.begin(), a.end(), cmp);
    vector<int> ans;
    int j = 0;
    while (j < n - 2 && Vector(mn, a[j].first) * Vector(mn, a[j + 1].first) == 0) {
        //cout << a[j].second << endl;
        ans.push_back(a[j].second);
        j++;
    }
    //cout << a[j].second << endl;
    ans.push_back(a[j].second);
    ans.push_back(in);
    reverse(ans.begin(), ans.end());
    if ((int)ans.size() == n && n > 1) {
        cout << "No solution" << endl;
        return 0;
    }
    for (int i = j + 1; i < n - 1; ++i) {
        ans.push_back(a[i].second);
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}
