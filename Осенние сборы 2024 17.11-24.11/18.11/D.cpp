#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("fast-math")

using namespace std;
using ld = long long;

ld vec(ld x, ld y, ld x2, ld y2) {
    return x * y2 - x2 * y;
}

long long vec2(long long x, long long y, long long x2, long long y2) {
    return x * y2 - x2 * y;
}

ld sc(ld x, ld y, ld x2, ld y2) {
    return x * x2 + y * y2;
}

bool ch(int x1, int y1, int x2, int y2, vector<pair<int, int>>&  a) {
    long long x = (x2 - x1), y = (y2 - y1);
    for (int i = 0; i < (int)a.size(); ++i) {
        if (vec2(x, y, a[i].first - x1, a[i].second - y1) <= 0) {
            return 1;
        }
    }
    return 0;
}

bool ch2(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3, ld x4, ld y4, vector<pair<int, int>>&  a) {
    for (int i = 0; i < (int)a.size(); ++i) {
        if (vec(x2 - x1, y2 - y1, a[i].first - x1, a[i].second - y1) <= 0 && vec(x3 - x2, y3 - y2, a[i].first - x2, a[i].second - y2) <= 0 &&
            vec(x4 - x3, y4 - y3, a[i].first - x3, a[i].second - y3) <= 0 && vec(x1 - x4, y1 - y4, a[i].first - x4, a[i].second - y4) <= 0) {
            return 1;
        }
    }
    return 0;
}

mt19937 rnd(179);

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    int q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        a[i].first *= 2;
        a[i].second *= 2;
    }
    //shuffle(a.begin(), a.end(), rnd);
    for (int i = 0; i < q; ++i) {
        int t, x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        x1 *= 2;
        y1 *= 2;
        x2 *= 2;
        y2 *= 2;
        //shuffle(a.begin(), a.end(), rnd);
        if (t == 1) {
            if (ch(x1, y1, x2, y2, a)) {
                cout << "Yes" << "\n";
            } else {
                cout << "No\n";
            }
        } else {
            int x = x2 - x1, y = y2 - y1;
            ld c1 = ld(x1 + x2) / 2, c2 = ld(y1 + y2) / 2;
            ld x3 = c1 - ld(y) / 2, y3 = c2 + ld(x) / 2;
            ld x4 = c1 + ld(y) / 2, y4 = c2 - ld(x) / 2;
            //cout << x1 << " " << y1 << " " << x2 << " " << y2 << " " << x3 << " " << y3 << " " << x4 << " " << y4 << endl;
            if (ch2(x1, y1, x3, y3, x2, y2, x4, y4, a)) {
                cout << "Yes" << '\n';
            } else {
                cout << "No" << '\n';
            }
        }
    }
    return 0;
}
