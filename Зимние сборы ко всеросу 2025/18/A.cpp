#define GLIBBCXX_ DEBUG
#include<bits/stdc++.h>

using namespace std;

map<long long, set<array<long long, 4>>> all[4][4];
const long long MAX = 2e5, INF = 2e18;
array<long long, 3> a[MAX];
array<long long, 3> to[MAX];
array<long long, 3> timme[MAX];
map<char, long long> ch;

long long solve(long long in) {
    auto [x, y, d] = a[in];
    if (d == 0) {
        auto it = all[0][2][x].upper_bound({y, -1, -1, -1});
        to[in][0] = (*it)[3];
        timme[in][0] = abs(y - (*it)[0]) / 2;
        it = all[3][3][x - y].upper_bound({x, -1, -1, -1});
        to[in][1] = (*it)[3];
        timme[in][1] = abs(x - (*it)[0]);
        it = all[2][1][x + y].upper_bound({y, -1, -1, -1});
        to[in][2] = (*it)[3];
        timme[in][2] = abs(y - (*it)[0]);
    } else if (d == 2) {
        auto it = all[0][0][x].upper_bound({y, -1, -1, -1});
        --it;
        to[in][0] = (*it)[3];
        timme[in][0] = abs(y - (*it)[0]) / 2;
        it = all[3][1][x - y].upper_bound({x, -1, -1, -1});
        --it;
        to[in][1] = (*it)[3];
        timme[in][1] = abs(x - (*it)[0]);
        it = all[2][3][x + y].upper_bound({y, -1, -1, -1});
        --it;
        to[in][2] = (*it)[3];
        timme[in][2] = abs(y - (*it)[0]);
    } else if (d == 1) {
        auto it = all[1][3][y].upper_bound({x, -1, -1, -1});
        to[in][0] = (*it)[3];
        timme[in][0] = abs(y - (*it)[0]) / 2;
        it = all[3][2][x - y].upper_bound({x, -1, -1, -1});
        to[in][1] = (*it)[3];
        timme[in][1] = abs(x - (*it)[0]);
        it = all[2][0][x + y].upper_bound({y, -1, -1, -1});
        --it;
        to[in][2] = (*it)[3];
        timme[in][2] = abs(y - (*it)[0]);
    } else {
        auto it = all[1][1][y].upper_bound({x, -1, -1, -1});
        --it;
        to[in][0] = (*it)[3];
        timme[in][0] = abs(y - (*it)[0]) / 2;
        it = all[3][0][x - y].upper_bound({x, -1, -1, -1});
        --it;
        to[in][1] = (*it)[3];
        timme[in][1] = abs(x - (*it)[0]);
        it = all[2][2][x + y].upper_bound({y, -1, -1, -1});
        to[in][2] = (*it)[3];
        timme[in][2] = abs(y - (*it)[0]);
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ch['S'] = 0;
    ch['E'] = 1;
    ch['N'] = 2;
    ch['W'] = 3;
    long long n;
    cin >> n;
    for (long long i = 0; i < n; ++i) {
        long long x, y;
        char d;
        cin >> x >> y >> d;
        long long c = ch[d];
        a[i] = {x, y, c};
        all[0][c][x].insert({y, x, c, i});
        all[1][c][y].insert({x, y, c, i});
        all[2][c][x + y].insert({y, x, c, i});
        all[3][c][x - y].insert({x, y, c, i});
    }
    for (long long i = 0; i < 4; ++i) {
        for (long long j = 0; j < 4; ++j) {
            for (long long k = 0; k < n; ++k) {
                all[i][j][a[k][0]].insert({INF, -1, -1, -1});
                all[i][j][a[k][0]].insert({-INF, -1, -1, -1});
                all[i][j][a[k][1]].insert({INF, -1, -1, -1});
                all[i][j][a[k][1]].insert({-INF, -1, -1, -1});
                all[i][j][a[k][0] + a[k][1]].insert({INF, -1, -1, -1});
                all[i][j][a[k][0] + a[k][1]].insert({-INF, -1, -1, -1});
                all[i][j][a[k][0] - a[k][1]].insert({INF, -1, -1, -1});
                all[i][j][a[k][0] - a[k][1]].insert({-INF, -1, -1, -1});
            }
        }
    }
    set<array<long long, 3>> q;
    for (long long i = 0; i < n; ++i) {
        solve(i);
        for (long long j = 0; j < 3; ++j) {
            q.insert({timme[i][j], i, to[i][j]});
        }
    }
    vector<long long> used(n, -1);
    while (!q.empty()) {
        auto [tm, in, in2] = (*q.begin());
        q.erase(q.begin());
        if (tm > 1e9) break;
        if (used[in] != -1 && used[in2] != -1) continue;
        if (used[in] != -1) {
            if (tm == used[in]) {
                used[in2] = tm;
                continue;
            }
            solve(in2);
            for (long long j = 0; j < 3; ++j) {
                q.insert({timme[in2][j], in2, to[in2][j]});
            }
            continue;
        }
        if (used[in2] != -1) {
            if (tm == used[in2]) {
                used[in] = tm;
                continue;
            }
            solve(in);
            for (long long j = 0; j < 3; ++j) {
                q.insert({timme[in][j], in, to[in][j]});
            }
            continue;
        }
        used[in] = tm;
        used[in2] = tm;
        auto [x, y, c] = a[in];
        all[0][c][x].erase({y, x, c, in});
        all[1][c][y].erase({x, y, c, in});
        all[2][c][x + y].erase({y, x, c, in});
        all[3][c][x - y].erase({x, y, c, in});
        auto [x2, y2, c2] = a[in2];
        all[0][c2][x2].erase({y2, x2, c2, in2});
        all[1][c2][y2].erase({x2, y2, c2, in2});
        all[2][c2][x2 + y2].erase({y2, x2, c2, in2});
        all[3][c2][x2 - y2].erase({x2, y2, c2, in2});
    }
    for (long long i = 0; i < n; ++i) {
        if (used[i] == -1) {
            cout << i + 1 << endl;
        }
    }
    return 0;
}
