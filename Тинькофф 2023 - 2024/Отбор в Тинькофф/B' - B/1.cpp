#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    while (true) {
        int st, dn, r;
        cin >> st >> dn >> r;
        if (st == 0 && dn == 0 && r == 0) break;
        st--;
        vector<int> ps(r);
        vector<vector<int>> ds(r);
        vector<vector<int>> ts(r);
        vector<vector<pair<int, int>>> ins(500);
        for (int i = 0; i < r; ++i) {
            int n;
            cin >> n >> ps[i];
            for (int j = 0; j < n; ++j) {
                int s;
                cin >> s;
                --s;
                ins[s].push_back({i, j});
                ds[i].push_back(s);
            }
            for (int j = 0; j < n; ++j) {
                int t;
                cin >> t;
                ts[i].push_back(t);
            }
        }
        vector<int> d(500, 1e18);
        vector<vector<int>> dp(r, vector<int> (200, 1e18));
        d[st] = 0;
        set<pair<int, pair<int, int>>> q;
        q.insert({0, {st, -1}});
        while (!q.empty()) {
            auto [i, j] = q.begin()->second;
            q.erase(q.begin());
            if (j == -1) {
                for (auto [num, k] : ins[i]) {
                    if (d[i] + dn < dp[num][k]) {
                        q.erase({dp[num][k], {num, k}});
                        dp[num][k] = d[i] + dn;
                        q.insert({dp[num][k], {num, k}});
                    }
                }
                continue;
            }
            if (j + 1 == ds[i].size()) continue;
            int len = ((dp[i][j] - ts[i][j] % ps[i]) + ps[i] - 1) / ps[i] * ps[i] + ts[i][j] % ps[i] - ts[i][j] + ts[i][j + 1];
            if (len < dp[i][j + 1]) {
                q.erase({dp[i][j + 1], {i, j + 1}});
                dp[i][j + 1] = len;
                if (dp[i][j + 1] < d[ds[i][j + 1]]) {
                    q.erase({d[ds[i][j + 1]], {ds[i][j + 1], -1}});
                    d[ds[i][j + 1]] = dp[i][j + 1];
                    q.insert({d[ds[i][j + 1]], {ds[i][j + 1], -1}});
                }
                q.insert({dp[i][j + 1], {i, j + 1}});
            }
        }
        cout << d[0] << endl;
    }
    return 0;
}
