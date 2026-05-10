#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> b;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int a;
            cin >> a;
            b.push_back({a, i});
        }
    }
    sort(b.begin(), b.end());
    vector<int> used(n);
    int cnt = 0;
    int r = 0;
    int minm = 2e9;
    pair<int, int> ans;
    for (int l = 0; l < (int)b.size(); ++l) {
        if (l != 0) {
            used[b[l - 1].second]--;
            if (!used[b[l - 1].second]) {
                cnt--;
            }
        }
        while (r < (int)b.size() && cnt < n) {
            if (!used[b[r].second]) {
                cnt++;
            }
            used[b[r].second]++;
            r++;
        }
        if (cnt >= n) {
            if (minm > b[r - 1].first - b[l].first) {
                minm = b[r - 1].first - b[l].first;
                ans = {l, r};
            }
        }
    }
    vector<int> used2(n);
    for (int i = ans.first; i < ans.second; ++i) {
        if (!used2[b[i].second]) {
            cout << b[i].first << " ";
        }
        used2[b[i].second] = 1;
    }
    return 0;
}
