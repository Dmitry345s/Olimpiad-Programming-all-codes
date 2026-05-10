#include<bits/stdc++.h>

#define int long long

using namespace std;

int MAX = 5e5 + 3;
vector<vector<vector<array<int, 3>>>> g(MAX);
vector<vector<int>> d(MAX);

signed main() {
    int n, l;
    cin >> n >> l;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
        g[x[i]].resize(n + 1);
        d[x[i]].assign(n + 1, 1e18);
    }
    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            for (int l = 0; l < n; ++l) {
                int c = abs(x[i] - x[j]) * (l + 1);
                g[x[i]][l].push_back({x[j], l + 1, c});
                //cout << x[i] << " " << x[j] << " " << l << " " << c << endl;
            }
        }
    }
    int qs;
    cin >> qs;
    for (int i = 0; i < qs; ++i) {
        int s, f, t;
        cin >> s >> f >> t;
        d[s].assign(n + 1, 1e18);
        d[f].assign(n + 1, 1e18);
        g[s].resize(n + 1);
        g[f].resize(n + 1);
        for (int j = 0; j < n; ++j) {
            int c = abs(s - x[j]);
            int c2 = abs(f - x[j]) * (n + 1);
            g[s][0].push_back({x[j], 1, c});
            g[x[j]][n].push_back({f, n, c2});
            d[x[j]].assign(n + 1, 1e18);
        }
        d[s][0] = 0;
        //cout << 0 << endl;
        set<array<int, 3>> q;
        q.insert({0, s, 0});
        while (!q.empty()) {
            auto [dist, v1, v2] = *q.begin();
            q.erase(q.begin());
            //cout << dist << " " << v1 << " " << v2 << endl;
            for (auto [to1, to2, c] : g[v1][v2]) {
                if (d[to1][to2] > d[v1][v2] + c) {
                    q.erase({d[to1][to2], to1, to2});
                    d[to1][to2] = d[v1][v2] + c;
                    q.insert({d[to1][to2], to1, to2});
                }
            }
        }
        //cout << d[f][n] << endl;
        if (d[f][n] + n <= t) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
        for (int j = 0; j < n; ++j) {
            g[s][0].pop_back();
            g[x[j]][n].pop_back();
        }
    }*/
    int qs;
    cin >> qs;
    for (int i = 0; i < qs; ++i) {
        int s, f, t;
        cin >> s >> f >> t;
        vector<vector<int>> dp((1 << n), vector<int>(n, 1e18));
        for (int j = 0; j < n; ++j) {
            dp[(1 << j)][j] = abs(s - x[j]);
        }
        for (int mask = 0; mask < (1 << n); ++mask) {
            int cnt = 0;
            for (int j = 0; j < n; ++j) {
                if ((mask >> j) & 1) {
                    cnt++;
                }
            }
            for (int j = 0; j < n; ++j) {
                if ((mask >> j) & 1 == 0) continue;
                for (int l = 0; l < n; ++l) {
                    dp[mask][j] = min(dp[mask][j], dp[mask ^ (1 << j)][l] + abs(x[l] - x[j]) * cnt);
                }
            }
        }
        int flag = 0;
        for (int j = 0; j < n; ++j) {
            if (dp[(1 << n) - 1][j] + abs(f - x[j]) * (n + 1) + n <= t) {
                flag = 1;
            }
        }
        if (flag) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
