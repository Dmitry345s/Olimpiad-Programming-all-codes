#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9 + 1;

int ch(vector<int> x, vector<int> y, vector<int> a, int c) {
    vector<pair<int, int>> all;
    for (int i = 0; i < (int)y.size(); ++i) {
        if (a[i] < c) continue;
        int l = y[i] - (a[i] - c);
        int r = y[i] + (a[i] - c);
        all.push_back({l, -1});
        all.push_back({r, 1});
    }
    for (int i = 0; i < (int)x.size(); ++i) {
        all.push_back({x[i], 0});
    }
    sort(all.begin(), all.end());
    int minm = 0;
    int now = 0;
    for (int i = 0; i < (int)all.size(); ++i) {
        now += all[i].second;
        if (all[i].second == 0) {
            minm = min(minm, now);
        }
    }
    return -minm;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> y(n), a(n);
    for (int i = 0; i < n; ++i) {
        cin >> y[i] >> a[i];
    }
    vector<int> x(m);
    for (int i = 0; i < m; ++i) {
        cin >> x[i];
    }
    int l = -1, r = 1e9 + 1;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        if (ch(x, y, a, c) >= k) {
            l = c;
        } else {
            r = c;
        }
    }
    cout << l << endl;
    return 0;
}
