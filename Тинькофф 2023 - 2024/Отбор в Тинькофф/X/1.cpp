#include<bits/stdc++.h>
#define int long long

using namespace std;

int MAX = 100;
vector<int> used(MAX), mt(MAX, -1);

bool try_kuhn(int v, vector<vector<int>> & g) {
    if (used[v]) return false;
    used[v] = 1;
    for (int to : g[v]) {
        if (mt[to] == -1 || try_kuhn(mt[to], g)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

bool get_max(vector<vector<int>> & g, int n) {
    mt.assign(MAX, -1);
    for (int i = 0; i < n; ++i) {
        used.assign(MAX, 0);
        try_kuhn(i, g);
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (mt[i] != -1) {
            cnt++;
        }
    }
    return cnt == n;
}

signed main() {
    int n;
    double t;
    cin >> n >> t;
    vector<double> dist(n), dist2(n);
    vector<pair<double, double>> nums(n), nums2(n);
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        dist[i] = min(1 - x, x);
        dist[i] = min(dist[i], min(y, 1 - y));
        nums[i] = {x, y};
    }
    for (int i = 0; i < n; ++i) {
        double x, y;
        cin >> x >> y;
        dist2[i] = min(1 - x, x);
        dist2[i] = min(dist2[i], min(y, 1 - y));
        nums2[i] = {x, y};
    }
    vector<pair<double, pair<int, int>>> g2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double rx = nums[i].first - nums2[j].first, ry = nums[i].second - nums2[j].second;
            double rdist = dist[i] + dist2[j] + sqrt(rx * rx + ry * ry) * 2;
            g2.push_back({rdist, {i, j}});
        }
    }
    sort(g2.begin(), g2.end());
    double l = -1, r = 4;
    while (l + 0.000001 < r) {
        double m = (l + r) / 2;
        vector<vector<int>> g(MAX);
        for (int i = 0; i < g2.size(); ++i) {
            if (g2[i].first > m) break;
            g[g2[i].second.first].push_back(g2[i].second.second);
        }
        if (get_max(g, n)) {
            r = m;
        } else {
            l = m;
        }
    }
    cout << setprecision(8) << r / t << endl;
    return 0;
}
