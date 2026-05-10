#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<set<int>> all(k);
    for (int j = 0; j < n; ++j) {
        int a;
        cin >> a;
        --a;
        all[a].insert(j);
    }
    set<pair<int, int>> now;
    for (int i = 0; i < k; ++i) {
        if (!all[i].empty()) {
            now.insert({*all[i].begin(), i});
        }
    }
    vector<vector<int>> ans;
    while ((int)now.size() == k) {
        int x = (*now.begin()).first;
        int x2 = (*now.rbegin()).first;
        if (x2 - x > m) {
            auto [tt, in] = *now.begin();
            now.erase(now.begin());
            all[in].erase(all[in].begin());
            if (!all[in].empty()) {
                now.insert({*all[in].begin(), in});
            }
            continue;
        }
        ans.push_back({});
        for (auto [tt, in] : now) {
            ans.back().push_back(tt);
        }
        now.clear();
        for (int j = 0; j < k; ++j) {
            all[j].erase(all[j].begin());
            if (!all[j].empty()) {
                now.insert({*all[j].begin(), j});
            }
        }
    }
    cout << (int)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        for (auto in : ans[i]) {
            cout << in + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
