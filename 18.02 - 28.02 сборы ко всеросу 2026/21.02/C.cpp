#include<bits/stdc++.h>

#define int long long

using namespace std;
using ld = long double;

struct Point {
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

istream& operator >> (istream& in, Point & a) {
    in >> a.x >> a.y;
    return in;
}

ostream& operator << (ostream& out, Point & a) {
    out << a.x << " " << a.y;
    return out;
}

bool operator == (Point a, Point b) {
    return a.x == b.x && a.y == b.y;
}

struct Vector {
    int x, y;
    Vector(int x = 0, int y = 0) : x(x), y(y) {}
    Vector(Point a, Point b) {
        x = b.x - a.x;
        y = b.y - a.y;
    }
    Vector(Point a) {
        x = a.x;
        y = a.y;
    }
    int get2() {
        return x * x + y * y;
    }
};

int operator % (Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}

int operator * (Vector a, Vector b) {
    return a.x * b.y - b.x * a.y;
}

mt19937 rnd(57);
const int LN = 20;

int better(Vector a, Vector b) {
    if (a * b == 0) return a.get2() > b.get2();
    return a * b > 0;
}

int better2(Vector a, Vector b) {
    if (a * b == 0) return a.get2() > b.get2();
    return a * b < 0;
}

int lw(Point p, vector<Point>& a) {
    int n = (int)a.size();
    int ans = rnd() % n;
    for (int i = LN - 1; i >= 0; --i) {
        int trl = (ans + (1 << i)) % n;
        int trr = (ans - (1 << i) % n + n) % n;
        if (better(Vector(p, a[trl]), Vector(p, a[ans]))) {
            ans = trl;
        }
        if (better(Vector(p, a[trr]), Vector(p, a[ans]))) {
            ans = trr;
        }
    }
    return ans;
}

int hg(Point p, vector<Point>& a) {
    int n = (int)a.size();
    int ans = rnd() % n;
    for (int i = LN - 1; i >= 0; --i) {
        int trl = (ans + (1 << i)) % n;
        int trr = (ans - (1 << i) % n + n) % n;
        if (better2(Vector(p, a[trl]), Vector(p, a[ans]))) {
            ans = trl;
        }
        if (better2(Vector(p, a[trr]), Vector(p, a[ans]))) {
            ans = trr;
        }
    }
    return ans;
}

vector<int> f(Point p, vector<Point>& a) {
    int n = (int)a.size();
    vector<int> ans;
    int mbi = hg(p, a);
    for (int dl = -1; dl <= 1; ++dl) {
        int i = (mbi + dl + n) % n;
        int j = (i + 1) % n;
        Vector v1 = Vector(p, a[i]);
        Vector v2 = Vector(p, a[j]);
        if (v1 * v2 == 0) {
            ans.push_back(i);
        }
    }
    return ans;
}

ld dist(Point a, Point b) {
    return sqrtl(Vector(a, b).get2());
}

const int INF = 1e18;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<vector<Point>> mn(n);
    vector<vector<pair<Point, int>>> mn2(n);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        for (int j = 0; j < k; ++j) {
            Point p;
            cin >> p;
            mn[i].push_back(p);
        }
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            Point p;
            int t;
            cin >> p;
            cin >> t;
            mn2[i].push_back({p, t});
        }
    }
    vector<ld> dp((int)mn2[0].size());
    for (int i = 0; i < (int)mn2[0].size(); ++i) {
        dp[i] = mn2[0][i].second;
    }
    for (int i = 1; i < n; ++i) {
        int nn = (int)mn[i].size();
        vector<ld> ndp((int)mn2[i].size(), INF);
        vector<vector<int>> ins((int)mn[i].size());
        vector<vector<int>> ins2((int)mn[i].size());
        for (int j = 0; j < (int)mn2[i].size(); ++j) {
            vector<int> nh = f(mn2[i][j].first, mn[i]);
            for (int rnh : nh) {
                ins2[(rnh + 1) % nn].push_back(j);
                ins[rnh].push_back(j);
            }
        }
        for (int j = 0; j < (int)mn2[i - 1].size(); ++j) {
            int l = lw(mn2[i - 1][j].first, mn[i]);
            int r = hg(mn2[i - 1][j].first, mn[i]);
            ld ndist = dist(mn[i][l], mn2[i - 1][j].first);
            int rl = l;
            while (rl != r) {
                for (int y : ins[rl]) {
                    if (mn2[i][y].first == mn[i][l] || mn2[i][y].first == mn[i][r]) continue;
                    ndp[y] = min(ndp[y], dp[j] + ndist + mn2[i][y].second + dist(mn[i][rl], mn2[i][y].first));
                }
                int wl = (rl + 1) % nn;
                ndist += dist(mn[i][rl], mn[i][wl]);
                rl = wl;
            }
            ndist = dist(mn[i][r], mn2[i - 1][j].first);
            int rr = r;
            while (rr != l) {
                for (int y : ins2[rr]) {
                    if (mn2[i][y].first == mn[i][l] || mn2[i][y].first == mn[i][r]) continue;
                    //cout << "* " << j << " " << y << endl;
                    ndp[y] = min(ndp[y], dp[j] + ndist + mn2[i][y].second + dist(mn[i][rr], mn2[i][y].first));
                }
                int wr = (rr - 1 + nn) % nn;
                ndist += dist(mn[i][rr], mn[i][wr]);
                rr = wr;
            }
        }
        dp = ndp;
        //cout << dp[2] << endl;
    }
    ld ans = INF;
    for (int i = 0; i < (int)mn2.back().size(); ++i) {
        ans = min(ans, dp[i] + dist(Point(), mn2.back()[i].first));
    }
    if (ans >= INF) {
        cout << -1 << endl;
    } else {
        cout << setprecision(30) << ans << endl;
    }
    return 0;
}
/*
2
4
2 2
-2 2
-2 -2
2 -2
1
-1 2 1
4
1 1
-1 1
-1 -1
1 -1
4
1 1 1
-1 1 1
-1 -1 1
1 -1 10
*/
