#include<bits/stdc++.h>

using namespace std;

const long long INF = 1e18, INF2 = 1e9;

mt19937 rnd(time(0));

struct Point {
    long long x, y;
    Point(long long x = 0, long long y = 0) : x(x), y(y) {};
};

long double get(Point a, Point b) {
    long long x1 = b.x - a.x, y1 = b.y - a.y;
    return sqrtl(x1 * x1 + y1 * y1);
}

signed main() {
    int n;
    cin >> n;
    vector<Point> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x >> a[i].y;
        a[i].x += INF2;
        a[i].y += INF2;
    }
    shuffle(a.begin(), a.end(), rnd);
    long long d = INF;
    long double rans = d;
    int now1 = -1, now2 = -1;
    int lasti = 0;
    while (true) {
        map<pair<long long, long long>, vector<int>> mp;
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            flag = 0;
            long long x = a[i].x / d;
            long long y = a[i].y / d;
            if (i < lasti) {
                mp[{x, y}].push_back(i);
                continue;
            }
            for (int del1 = -1; del1 <= 1; ++del1) {
                for (int del2 = -1; del2 <= 1; ++del2) {
                    long long x1 = x + del1, y1 = y + del2;
                    for (auto j : mp[{x1, y1}]) {
                        if (rans > get(a[i], a[j])) {
                            flag = 1;
                            rans = get(a[i], a[j]);
                            d = get(a[i], a[j]);
                            now1 = i;
                            now2 = j;
                        }
                    }
                }
            }
            mp[{x, y}].push_back(i);
            if (flag == 1) {
                lasti = i;
                break;
            }
        }
        if (flag == 0) {
            break;
        }
    }
    cout << a[now1].x - INF2 << " " << a[now1].y - INF2 << endl;
    cout << a[now2].x - INF2 << " " << a[now2].y - INF2 << endl;
    //cout << setprecision(20) << rans << endl;
    return 0;
}
