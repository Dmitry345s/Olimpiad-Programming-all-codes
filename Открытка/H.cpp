#include<bits/stdc++.h>

#define int long long

using namespace std;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

istream& operator >> (istream & in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0): x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
};

int operator * (Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

bool check(long long a, long long b) {
    return (a <= 0 && b <= 0) || (a >= 0 && b >= 0);
}

bool in_angle(Point a, Point o, Point b, Point p) {
    Vector s1 = Vector(o, a), s2 = Vector(o, b), ch = Vector(o, p);
    if (check(s1 * s2, s1 * ch) && check(s2 * s1, s2 * ch)) {
        return 1;
    }
    return 0;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    /*if (n == 3 && q == 0) {
        Point c;
        cin >> c;
        vector<Point> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        vector<int> u(3);
        for (int i = 0; i < m; ++i) {
            Point newp;
            cin >> newp;
            if (in_angle(a[0], c, a[1], newp)) {
                u[0] += 1;
            } else if (in_angle(a[1], c, a[2], newp)) {
                u[1] += 1;
            } else {
                u[2] += 1;
            }
        }
        //cout << u[0] << " " << u[1] << " " << u[2] << endl;
        if (u[0] && u[1] && u[2] || m == 0) {
            cout << "Bob" << endl;
        } else {
            cout << "Alice" << endl;
        }
    }*/
    if (n <= 18) {
        vector<int> dp(1 << n);
        dp[0] = 0;
        for (int i = 1; i < (1 << n); ++i) {
            int ch = 1;
            for (int j = 0; j < n; ++j) {
                int rn = i;
                int j2 = (j + 1) % n;
                if (!((i >> j) & 1) && !((i >> j2) & 1)) continue;
                if ((i >> j) & 1) {
                    rn ^= (1 << j);
                }
                if ((i >> j2) & 1) {
                    rn ^= (1 << j2);
                }
                ch &= dp[rn];
            }
            dp[i] = !ch;
        }
        Point c;
        cin >> c;
        vector<Point> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        int mask = 0;
        vector<int> cnt(n);
        for (int i = 0; i < m; ++i) {
            Point newp;
            cin >> newp;
            for (int j = 0; j < n; ++j) {
                int j2 = (j + 1) % n;
                if (in_angle(a[j], c, a[j2], newp)) {
                    cnt[j]++;
                    if (cnt[j] == 1) {
                        mask ^= (1 << j);
                    }
                }
            }
        }
        if (dp[mask]) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
        for (int i = 0; i < q; ++i) {
            char p;
            cin >> p;
            Point newp;
            cin >> newp;
            for (int j = 0; j < n; ++j) {
                int j2 = (j + 1) % n;
                if (in_angle(a[j], c, a[j2], newp)) {
                    if (p == '+') {
                        cnt[j]++;
                        if (cnt[j] == 1) {
                            mask ^= (1 << j);
                        }
                    } else {
                        cnt[j]--;
                        if (cnt[j] == 0) {
                            mask ^= (1 << j);
                        }
                    }
                }
            }
            if (dp[mask]) {
                cout << "Alice" << '\n';
            } else {
                cout << "Bob" << '\n';
            }
        }
    }
    return 0;
}
