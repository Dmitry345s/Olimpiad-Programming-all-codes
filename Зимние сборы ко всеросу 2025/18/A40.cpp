#include<bits/stdc++.h>

using namespace std;

map<char, long long> ch;
map<int, pair<int, int>> ch2;

const int INF = 2e9;

signed main() {
    ch['S'] = 0;
    ch['E'] = 1;
    ch['N'] = 2;
    ch['W'] = 3;
    ch2[0] = {0, 1};
    ch2[1] = {1, 0};
    ch2[2] = {0, -1};
    ch2[3] = {-1, 0};
    int n;
    cin >> n;
    vector<array<int, 3>> a(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        char d;
        cin >> x >> y;
        cin >> d;
        int c = ch[d];
        a[i] = {x, y, c};
    }
    vector<array<int, 3>> all;
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            int t1 = abs(a[i][0] - a[j][0]) / 2;
            int t2 = abs(a[i][1] - a[j][1]) / 2;
            int t3 = abs(a[i][0] - a[j][0]);
            int x = a[i][0], y = a[i][1];
            auto [delx, dely] = ch2[a[i][2]];
            int x2 = a[j][0], y2 = a[j][1];
            auto [delx2, dely2] = ch2[a[j][2]];
            int now = INF;
            if (x + delx * t1 == x2 + delx2 * t1 && y + dely * t1 == y2 + dely2 * t1) {
                now = min(now, t1);
            }
            if (x + delx * t2 == x2 + delx2 * t2 && y + dely * t2 == y2 + dely2 * t2) {
                now = min(now, t2);
            }
            if (x + delx * t3 == x2 + delx2 * t3 && y + dely * t3 == y2 + dely2 * t3) {
                now = min(now, t3);
            }
            if (now != INF) {
                all.push_back({now, i, j});
            }
        }
    }
    vector<int> used(n, -1);
    sort(all.begin(), all.end());
    for (int i = 0; i < (int)all.size(); ++i) {
        auto [tm, in, in2] = all[i];
        if (used[in] != -1 && used[in2] != -1) continue;
        if (used[in] != -1) {
            if (tm == used[in]) {
                used[in2] = tm;
                continue;
            }
            continue;
        }
        if (used[in2] != -1) {
            if (tm == used[in2]) {
                used[in] = tm;
                continue;
            }
            continue;
        }
        used[in] = tm;
        used[in2] = tm;
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == -1) {
            cout << i + 1 << endl;
        }
    }
    return 0;
}
