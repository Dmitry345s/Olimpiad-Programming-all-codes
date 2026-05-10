#include<bits/stdc++.h>

#define int long long

using namespace std;

int ch(int x, vector<array<int, 3>> all, int m) {
    vector<vector<int>> now(m + 1, vector<int> (m + 1, -x));
    for (int i = 0; i < m + 1; ++i) {
        for (int j = 0; j < i; ++j) {
            now[i][j] = 0;
        }
    }
    for (auto [x, y, s] : all) {
        now[x][y] += s;
    }
    vector<vector<int>> pref(m + 2, vector<int> (m + 2));
    for (int i = 1; i <= m + 1; ++i) {
        for (int j = 1; j <= m + 1; ++j) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + now[i - 1][j - 1];
            if (pref[i][j] < 0) {
                return 0;
            }
        }
    }
    return 1;
}

signed main() {
    int m, v;
    cin >> m >> v;
    vector<array<int, 3>> all;
    for (int i = 0; i < v; ++i) {
        int x, y, s;
        cin >> x >> y >> s;
        if (x > y) {
            swap(x, y);
        }
        all.push_back({x, y, s});
    }
    int l = 0, r = 8e18;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        //cout << l << " " << r << " " << c << endl;
        if (ch(c, all, m)) {
            l = c;
        } else {
            r = c;
        }
    }
    cout << l << endl;
    return 0;
}
