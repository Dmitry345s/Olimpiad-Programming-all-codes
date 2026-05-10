#include<bits/stdc++.h>
#pragma GCC optimize("O3")

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

bool in_angle(Point a, Point o, Point b, Point p) {
    Vector v1 = Vector(o, a), v2 = Vector(o, b), v3 = Vector(o, p);
    ll x1 = v1 * v2, x2 = v1 * v3, x3 = v2 * v1, x4 = v2 * v3;
    return ((x1 <= 0 && x2 <= 0) || (x1 >= 0 && x2 >= 0)) && ((x3 <= 0 && x4 <= 0) || (x3 >= 0 && x4 >= 0));
}

bool in_pol(vector<Point> & a, Point p) {
    int n = (int)a.size();
    int l = 0, r = n;
    Vector v1 = Vector(a[0], p);
    while (l + 1 < r) {
        int m = (l + r) / 2;
        Vector v2 = Vector(a[0], a[m]);
        if (v1 * v2 >= 0) {
            r = m;
        } else {
            l = m;
        }
    }
    if (r == n || r == 1) {
        return 0;
    }
    if (p == a[0] || p == a[l] || p == a[r] || (Vector(a[l], p) * Vector(a[r], p) == 0 && (Vector(a[l], p) ^ Vector(a[r], p)) < 0)) {
        return 0;
    }
    return in_angle(a[0], a[l], a[r], p) && in_angle(a[l], a[0], a[r], p) && in_angle(a[l], a[r], a[0], p);
}

bool check(vector<Point> & a, vector<Point> & b) {
    int flag = 1;
    for (int i = 0; i < (int)a.size(); ++i) {
        if (!in_pol(b, a[i])) {
            flag = 0;
        }
    }
    return flag;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, w, h;
    cin >> n >> w >> h;
    int mod = 998244353;
    vector<vector<Point>> a(n);
    vector<pair<ll, int>> b(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        a[i].resize(k);
        for (int j = 0; j < k; ++j) {
            cin >> a[i][j];
        }
        ll now = 0;
        for (int j = 0; j < k; ++j) {
            int j2 = (j + 1) % k;
            now += (a[i][j].x - a[i][j2].x) * (a[i][j].y + a[i][j2].y);
        }
        b[i] = {now, i};
    }
    sort(b.rbegin(), b.rend());
    vector<array<ll, 4>> dp(n + 1);
    dp[0] = {1, 1, 1, 1};
    vector<Point> ch1, ch2;
    for (int i = 1; i < n; ++i) {
        int l1 = b[i - 1].second, l2 = b[i].second;
        //cout << l1 << " " << l2 << endl;
        for (int m1 = 0; m1 < 4; ++m1) {
            for (int m2 = 0; m2 < 4; ++m2) {
                ch1 = a[l1]; ch2 = a[l2];
                for (int j = 0; j < (int)ch1.size(); ++j) {
                    if (m1 == 1) {
                        ch1[j].x = w - ch1[j].x;
                        ch1[j].y = h - ch1[j].y;
                    } else if (m1 == 2) {
                        ch1[j].x = w - ch1[j].x;
                    } else if (m1 == 3) {
                        ch1[j].y = h - ch1[j].y;
                    }
                }
                if (m1 == 2 || m1 == 3) {
                    reverse(ch1.begin(), ch1.end());
                }
                for (int j = 0; j < (int)ch2.size(); ++j) {
                    if (m2 == 1) {
                        ch2[j].x = w - ch2[j].x;
                        ch2[j].y = h - ch2[j].y;
                    } else if (m2 == 2) {
                        ch2[j].x = w - ch2[j].x;
                    } else if (m2 == 3) {
                        ch2[j].y = h - ch2[j].y;
                    }
                }
                if (m2 == 2 || m2 == 3) {
                    reverse(ch2.begin(), ch2.end());
                }
                /*cout << m1 << " " << m2 << " " << check(ch2, ch1) << endl;
                for (int j = 0; j < (int)ch2.size(); ++j) {
                    cout << "{" << ch2[j].x << ", " << ch2[j].y << "} ";
                }
                cout << endl;*/
                if (check(ch2, ch1)) {
                    dp[i][m2] += dp[i - 1][m1];
                    if (dp[i][m2] >= mod) {
                        dp[i][m2] -= mod;
                    }
                }
            }
        }
    }
    cout << (dp[n - 1][0] + dp[n - 1][1] + dp[n - 1][2] + dp[n - 1][3]) % mod << endl;
    return 0;
}
