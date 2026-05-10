#include<bits/stdc++.h>

using namespace std;

const int MAX = 500 + 5, MAX2 = 1005;
const long long INF = 1e18;
vector<int> used(MAX2);
vector<int> now_pair(MAX);
vector<pair<int, int>> coords;
vector<pair<int, int>> prt(MAX);
int timer = 1;

long long get(pair<int, int> a, pair<int, int> b) {
    long long x = a.first - b.first, y = a.second - b.second;
    return x * x + y * y;
}

bool try_kuhn(int v, int n, long long x) {
    if (used[v] == timer) return 0;
    used[v] = timer;
    for (int i = 0; i < n; ++i) {
        long long now = get(prt[i], coords[v]);
        if (now > x) continue;
        if (now_pair[i] == -1) {
            now_pair[i] = v;
            return 1;
        }
    }
    for (int i = 0; i < n; ++i) {
        long long now = get(prt[i], coords[v]);
        if (now > x) continue;
        if (try_kuhn(now_pair[i], n, x)) {
            now_pair[i] = v;
            return 1;
        }
    }
    return 0;
}

bool check(long long x, int n) {
    for (int i = 0; i < n; ++i) {
        now_pair[i] = -1;
    }
    for (int i = 0; i < (int)coords.size(); ++i) {
        used[i] = 0;
    }
    timer = 1;
    for (int i = 0; i < (int)coords.size(); ++i) {
        if (try_kuhn(i, n, x)) {
            timer++;
        }
    }
    return timer - 1 == n;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> prt[i].first >> prt[i].second;
    }
    vector<pair<int, int>> whr(m);
    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> whr[i].first >> whr[i].second >> a[i];
        for (int j = 0; j < a[i]; ++j) {
            coords.push_back(whr[i]);
        }
    }
    long long l = 0, r = INF;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (check(m, n)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << setprecision(20) << sqrtl(r) << endl;
    return 0;
}
