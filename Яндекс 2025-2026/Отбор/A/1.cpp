#include<bits/stdc++.h>

using namespace std;
using ld = long double;

const ld EPS = 1e-1;

bool in(pair<ld, ld> u, pair<ld, ld> d, pair<int, int> p) {
    ld f = u.first * p.first + u.second - p.second;
    ld s = d.first * p.first + d.second - p.second;
    return s * f <= 0;
}

signed main() {
    int r, c, k;
    cin >> r >> c >> k;
    ld kk = (ld)(c - 1) / (ld)(r - 1);
    pair<ld, ld> l1 = {kk, -kk}, l2 = {kk, 1};
    vector<pair<int, int>> d, u;
    d.push_back({1, 0});
    d.push_back({r, c - 1});
    u.push_back({0, 1});
    u.push_back({r - 1, c});
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        int in1 = in(l2, l1, {x - 1, y});
        int in2 = in(l2, l1, {x, y - 1});
        if (in1 && in2) {
            cout << 0 << endl;
            return 0;
        }
        if (in1) {
            d.push_back({x - 1, y});
        }
        if (in2) {
            u.push_back({x, y - 1});
        }
    }
    ld lk = -1e9, rk = 1e9;
    for (auto [x1, y1] : d) {
        for (auto [x2, y2] : u) {
            if (x1 == x2) {
                if (y2 <= y1) {
                    cout << 0 << endl;
                    return 0;
                }
                continue;
            }
            if (x1 > x2) {
                lk = max(lk, (ld)(y1 - y2) / (ld)(x1 - x2));
            } else {
                rk = min(rk, (ld)(y2 - y1) / (ld)(x2 - x1));
            }
        }
    }
    /*for (ld nowk = lk + EPS; nowk < rk; nowk += EPS) {
        ld mx = -1e9;
        for (auto [x1, y1] : d) {
            mx = max(mx, y1 - nowk * x1);
        }
        ld mn = 1e9;
        for (auto [x2, y2] : u) {
            mn = min(mn, y2 - nowk * x2);
        }
        //cout << nowk << " " << mn << " " << mx << endl;
        if (mn - mx > 0) {
            cout << 1 << endl;
            return 0;
        }
    }*/
    cout << (rk - lk > 0) << endl;
    return 0;
}
