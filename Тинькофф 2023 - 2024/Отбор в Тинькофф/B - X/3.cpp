#include<bits/stdc++.h>
#define int long long

using namespace std;

int MIN = -1e9;
double EPS = 1e-5;

bool equals(double a, double b) {
    return abs(a - b) < EPS;
}

struct Point {
    int x, y;
    Point(int x = 1e9, int y = 1e9): x(x), y(y) {}
};

struct Vector {
    int x, y;
    Vector(int x = 1e9, int y = 1e9): x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator ^ (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool operator < (Point a, Point b) {
    if (a.y == b.y) {
        return a.x > b.x;
    }
    return a.y < b.y;
}

istream& operator >> (istream & in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

double dist2(Vector a) {
    return a.x * a.x + a.y * a.y;
}

double get(vector<Point> a) {
    int n = a.size();
    if (n == 2) {
        return dist2(Vector(a[0], a[1]));
    }
    double ans = 0;
    for (int i = 0; i < n - 1; ++i) {
        ans += double(Vector(a[i].x, a[i].y) * Vector(a[i + 1].x, a[i + 1].y)) / 2;
    }
    ans += double(Vector(a[n - 1].x, a[n - 1].y) * Vector(a[0].x, a[0].y)) / 2;
    return abs(ans);
}

vector<Point> getobl(vector<Point> & a2) {
    pair<Point, int> mn = {{MIN, -MIN}, -1};
    int n = a2.size();
    vector<pair<Point, int>> a(n);
    for (int i = 0; i < n; ++i) {
        a[i].first = a2[i];
        a[i].second = i;
        mn = min(mn, a[i]);
    }
    swap(a[mn.second], a.back());
    a.pop_back();
    sort(a.begin(), a.end(), [&] (pair<Point, int> a, pair<Point, int> b) {
        if (Vector(mn.first, a.first) * Vector(mn.first, b.first) == 0) {
            return dist2(Vector(mn.first, a.first)) < dist2(Vector(mn.first, b.first));
         }
         return Vector(mn.first, a.first) * Vector(mn.first, b.first) > 0;
        });
    vector<Point> ans;
    ans.push_back(mn.first);
    ans.push_back(a[0].first);
    for (int i = 1; i < n - 1; ++i) {
        int k = ans.size();
        while (k >= 2 && (Vector(ans[k - 2], ans[k - 1]) * Vector(ans[k - 1], a[i].first)) <= 0) {
            ans.pop_back();
            --k;
        }
        ans.push_back(a[i].first);
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    vector<Point> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    if (n == 2) {
        cout << 1 << endl;
        return 0;
    }
    double kf = double(get(getobl(b))) / get(getobl(a));
    //cout << kf << endl;
    //cout << kf * get(getobl(a)) << endl;
    vector<double> dista(n), distb(n), ana(n), anb(n);
    for (int i = 0; i < n; ++i) {
        int j = (i - 1 + n) % n;
        int l = (i + 1) % n;
        dista[i] = dist2(Vector(a[i], a[l])) * kf;
        distb[i] = dist2(Vector(b[i], b[l]));
        Vector v1 = Vector(a[i], a[j]), v2 = Vector(a[i], a[l]);
        ana[i] = atan2(v1 ^ v2, v1 * v2);
        Vector v3 = Vector(b[i], b[j]), v4 = Vector(b[i], b[l]);
        anb[i] = atan2(v3 ^ v4, v3 * v4);
        //cout << dista[i] << " " << distb[i] << " " << ana[i] << " " << anb[i] << endl;
    }
    vector<pair<double, double>> s;
    for (int i = 0; i < n; ++i) {
        s.push_back({dista[i], ana[i]});
    }
    s.push_back({1e9, 1e9});
    for (int i = 0; i < 2 * n; ++i) {
        int j = i % n;
        s.push_back({distb[j], anb[j]});
    }
    vector<int> z(s.size());
    z[0] = s.size();
    int l = 0, r = 1;
    //cout << s[0].first << " " << s[0].second << endl;
    for (int i = 1; i < z.size(); ++i) {
        //cout << s[i].first << " " << s[i].second << endl;
        if (i < r) {
            z[i] = min(z[i - l], max((long long) 0, r - i));
        }
        while (i + z[i] < s.size() && equals(s[z[i]].first, s[z[i] + i].first) && equals(s[z[i]].second, s[z[i] + i].second)) {
            ++z[i];
        }
        if (z[i] + i > r) {
            r = z[i] + i;
            l = i;
        }
        if (z[i] == n) {
            //cout << i << endl;
            cout << i - n << endl;
            return 0;
        }
    }
    cout << 0 << endl;
    return 0;
}
