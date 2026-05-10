#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 2e15;

signed main() {
    int n;
    cin >> n;
    vector<array<int, 3>> all(n);
    vector<int> u;
    for (int i = 0; i < n; ++i) {
        cin >> all[i][0] >> all[i][1] >> all[i][2];
        u.push_back(all[i][1]);
    }
    sort(u.begin(), u.end());
    u.erase(unique(u.begin(), u.end()), u.end());
    vector<vector<array<int, 3>>> tr((int)u.size());
    for (int i = 0; i < n; ++i) {
        all[i][1] = lower_bound(u.begin(), u.end(), all[i][1]) - u.begin();
        tr[all[i][1]].push_back({-1, all[i][0], all[i][2]});
    }
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        int c, f, v;
        cin >> c >> f >> v;
        f = lower_bound(u.begin(), u.end(), f) - u.begin();
        if (f == (int)u.size()) continue;
        tr[f].push_back({1, c, v});
    }
    vector<int> bag(50 * n + 1, -INF);
    bag[0] = 0;
    for (int i = (int)u.size() - 1; i >= 0; --i) {
        sort(tr[i].begin(), tr[i].end());
        for (auto [tp, c, v] : tr[i]) {
            if (tp == -1) {
                for (int j = (int)bag.size() - 1; j >= c; --j) {
                    bag[j] = max(bag[j], bag[j - c] - v);
                }
            } else {
                for (int j = 0; j < (int)bag.size() - c; ++j) {
                    bag[j] = max(bag[j], bag[j + c] + v);
                }
            }
        }
    }
    int ans = 0;
    for (int i = 0; i < (int)bag.size(); ++i) {
        ans = max(ans, bag[i]);
    }
    cout << ans << endl;
    return 0;
}
