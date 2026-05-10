#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 1;

int solve(vector<int> all, vector<pair<int, int>> now) {
    vector<int> dt;
    for (int i = 0; i < (int)all.size() - 1; ++i) {
        dt.push_back(all[i + 1] - all[i]);
    }
    int n = (int)dt.size();
    vector<int> ch(n);
    int bl = 0;
    vector<int> dif(n + 1);
    for (int i = 0; i < (int)now.size(); ++i) {
        dif[now[i].first]++;
        dif[now[i].second]--;
    }
    for (int i = 0; i < n; ++i) {
        bl += dif[i];
        if (bl > 0) {
            ch[i] = 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (ch[i]) {
            ans = max(ans, dt[i]);
        }
    }
    return ans;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> all(n + 1);
    for (int i = 0; i <= n; ++i) cin >> all[i].first >> all[i].second;
    map<int, vector<int>> xs;
    map<int, vector<int>> ys;
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        xs[x].push_back(y);
        ys[y].push_back(x);
    }
    for (auto & [key, val] : xs) sort(val.begin(), val.end());
    for (auto & [key, val] : ys) sort(val.begin(), val.end());
    map<int, vector<pair<int, int>>> qxs;
    map<int, vector<pair<int, int>>> qys;
    int ans = 0;
    int las = 0;
    for (int i = 0; i < n; ++i) {
        int j = i + 1;
        if (all[i].first == all[j].first) {
            int x = all[i].first;
            int ls = min(all[i].second, all[j].second);
            int rs = max(all[i].second, all[j].second);
            int l = lower_bound(xs[x].begin(), xs[x].end(), ls) - xs[x].begin();
            int r = upper_bound(xs[x].begin(), xs[x].end(), rs) - xs[x].begin() - 1;
            if (r - l + 1 <= 0) {
                las += rs - ls;
                continue;
            }
            qxs[x].push_back({l, r});
            if (abs(xs[x][l] - all[i].second) < abs(xs[x][r] - all[i].second)) {
                ans = max(ans, las + abs(xs[x][l] - all[i].second));
                las = abs(xs[x][r] - all[j].second);
            } else {
                ans = max(ans, las + abs(xs[x][r] - all[i].second));
                las = abs(xs[x][l] - all[j].second);
            }
        } else {
            int y = all[i].second;
            int ls = min(all[i].first, all[j].first);
            int rs = max(all[i].first, all[j].first);
            int l = lower_bound(ys[y].begin(), ys[y].end(), ls) - ys[y].begin();
            int r = upper_bound(ys[y].begin(), ys[y].end(), rs) - ys[y].begin() - 1;
            if (r - l + 1 <= 0) {
                las += rs - ls;
                continue;
            }
            qys[y].push_back({l, r});
            if (abs(ys[y][l] - all[i].first) < abs(ys[y][r] - all[i].first)) {
                ans = max(ans, las + abs(ys[y][l] - all[i].first));
                las = abs(ys[y][r] - all[j].first);
            } else {
                ans = max(ans, las + abs(ys[y][r] - all[i].first));
                las = abs(ys[y][l] - all[j].first);
            }
        }
    }
    ans = max(ans, las);
    for (auto [x, key] : xs) {
        ans = max(ans, solve(key, qxs[x]));
    }
    for (auto [y, key] : ys) {
        ans = max(ans, solve(key, qys[y]));
    }
    cout << max(0ll, ans - 100) << endl;
    return 0;
}
