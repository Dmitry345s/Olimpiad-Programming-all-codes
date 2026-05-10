#include<bits/stdc++.h>

using namespace std;

int n;

bool in(pair<int, int> seg, int p) {
    if (seg.first <= seg.second) {
        return seg.first <= p && p <= seg.second;
    } else {
        return (seg.first <= p && p <= n - 1) || (0 <= p && p <= seg.second);
    }
}

int get (pair<int, int> seg) {
    if (seg.first <= seg.second) {
        return seg.second - seg.first + 1;
    } else {
        return n - 1 - seg.first + 1 + seg.second - 1 + 1;
    }
}

signed main() {
    int m;
    cin >> n >> m;
    vector<pair<int, int>> all;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        all.push_back({a, b});
    }
    /*vector<vector<array<int, 2>>> dp(n, vector<array<int, 2>> (n, {-1, -1}));
    for (int d = 2; d < n; ++d) {
        for (int l = 0; l < n; ++l) {
            int r = (l + d) % n;
            for (int i = 0; i < m; ++i) {
                if (!in(all[i], r) || !in({l, r}, all[i].first)) continue;
                for (int j = 0; j < m; ++j) {
                    if (!in(all[j], r) || !in({l, r}, all[j].first)) continue;

                }
            }
        }
    }*/
    vector<vector<int>> dp(n, vector<int> (n, 1e9));
    vector<vector<int>> p(n, vector<int> (n, -1));
    for (int i = 0; i < m; ++i) {
        dp[all[i].first][all[i].second] = 0;
        p[all[i].first][all[i].second] = i;
    }
    for (int d = 1; d <= n; ++d) {
        for (int l = 0; l < n; ++l) {
            int r = (l + d - 1) % n;
            for (int i = 0; i < m; ++i) {
                if (!in(all[i], r) || !in({l, r}, all[i].first)) continue;
                if (dp[l][r] > dp[l][all[i].first] + get({all[i].first, r})) {
                    dp[l][r] = dp[l][all[i].first] + get({all[i].first, r});
                    p[l][r] = i;
                }
            }
        }
    }
    //cout << 0 << endl;
    int minm = 1e9;
    int ind = -1;
    for (int i = 0; i < n; ++i) {
        if (dp[i][(i + n - 1) % n] < minm) {
            minm = dp[i][(i + n - 1) % n];
            ind = i;
        }
    }
    //cout << 0 << endl;
    int l = ind, r = (ind + n - 1) % n;
    vector<int> used(n);
    while (true) {
        //cout << l << " " << r << endl;
        int j = p[l][r];
        used[j] = 1;
        r = all[j].first;
        if (l == r) break;
    }
    //cout << 0 << endl;
    vector<int> used2(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (used[j]) continue;
            if (in(all[j], i)) continue;
            used2[i] = 1;
        }
    }
    int flag = 1;
    for (int i = 0; i < n; ++i) {
        if (used2[i] == 0) {
            flag = 0;
        }
    }
    if (!flag) {
        cout << "impossible" << endl;
        return 0;
    }
    for (int i = 0; i < m; ++i) {
        cout << used[i];
    }
    return 0;
}
