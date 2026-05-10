#include<bits/stdc++.h>

#define int long long

using namespace std;
using ld = long double;
using ll = long long;

struct Line {
    ld a, b, c;
    Line(int a = 0, int b = 0, int c = 0) : a(a), b(b), c(c) {};
    Line(int x1, int y1, int x2, int y2) {
        a = y2 - y1;
        b = x1 - x2;
        c = y1 * x2 - x1 * y2;
    }
};

const int INF = 1e9;

/*pair<ld, ld> gg(int r, Line now) {
    int a = now.a;
    int b = now.b;
    int c = now.c;
    if (now.a != 0) {
        ll d = 4 * b * b * c * c - 4 * (a * a + b * b) * (c * c - a * a * r * r);
        //cout << d << endl;
        if (d < 0) {
            return {INF, INF};
        } else {
            ld x1 = (-(2 * b * c) + sqrtl(d)) / (2 * (a * a + b * b));
            ld x2 = (-(2 * b * c) - sqrtl(d)) / (2 * (a * a + b * b));
            return {min(x1, x2), max(x1, x2)};
        }
    } else {
        ld d = r * r - ((ld)(c * c) / (ld)(b * b));
        return {-sqrtl(d), sqrtl(d)};
    }
}*/


signed main() {
    int n, R;
    cin >> n >> R;
    ld RR = R;
    vector<pair<int, int>> all;
    for (int i = 0; i < n; ++i) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (y1 == y2) {
            swap(x1, y1);
            swap(x2, y2);
        }
        ld dely = y2 - y1;
        if (dely > 0) {
            x1 *= -1;
            x2 *= -1;
            y2 *= -1;
            y1 *= -1;
            dely *= -1;
        }
        Line now = Line(x1, y1, x2, y2);
        //cout << now.a << " " << now.b << " " << now.c << endl;
        int l = -1e8 - 1, r = 1e8 + 1;
        int nl = 0;
        ld a = (now.a * now.a + now.b * now.b);
        ld b = (now.b * now.c * 2);
        ld c = (now.c * now.c - now.a * now.a * RR * RR);
        //cout << (ll)a << " " << (ll)b << " " << (ll)c << endl;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            ld ny = y1 + dely * m;
            ld cnt1 = a * ny * ny + b * ny + c;
            int cnt2 = (-b < ny * 2 * a);
            //cout << ny << " " << cnt2 << endl;
            if (cnt1 <= 0) {
                r = m;
            } else {
                if (cnt2 == 1) {
                    l = m;
                } else {
                    r = m;
                }
            }
        }
        nl = r;
        int nr;
        l = -1e8 - 1;
        r = 1e8 + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            ld ny = y1 + dely * m;
            ld cnt1 = a * ny * ny + b * ny + c;
            int cnt2 = (-b < ny * 2 * a);
            if (cnt1 <= 0) {
                l = m;
            } else {
                if (cnt2 == 1) {
                    l = m;
                } else {
                    r = m;
                }
            }
        }
        nr = l;
        all.push_back({nl, nr});
        //cout << nl << " " << nr << endl;
    }
    vector<pair<int, int>> to_ans;
    for (auto [l, r] : all) {
        if (r < 0) continue;
        l = max(l, 0ll);
        to_ans.push_back({r + 1, -1});
        to_ans.push_back({l, 1});
    }
    sort(to_ans.begin(), to_ans.end());
    int now = 0;
    int ans = 0;
    for (auto [x, tp] : to_ans) {
        now += tp;
        ans = max(ans, now);
    }
    cout << ans << endl;
    return 0;
}
