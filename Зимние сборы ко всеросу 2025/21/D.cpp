#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> all(n);
    vector<vector<pair<int, int>>> del(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        all[a].push_back({b, i});
        del[b].push_back({a, i});
    }
    for (int i = 0; i < n; ++i) {
        sort(all[i].begin(), all[i].end());
        sort(del[i].rbegin(), del[i].rend());
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < (1 << m); ++i) {
        //cout << i << endl;
        ans.clear();
        deque<int> gg;
        int fl = 1;
        for (int j = 0; j < n; ++j) {
            for (auto [num, k] : del[j]) {
                if (num == j) {
                    gg.push_front(k);
                    ans.push_back({1, k + 1});
                }
                if (gg.front() == k) {
                    gg.pop_front();
                    ans.push_back({3, k + 1});
                } else if (gg.back() == k) {
                    gg.pop_back();
                    ans.push_back({3, k + 1});
                } else {
                    fl = 0;
                }
            }
            for (auto [num, k] : all[j]) {
                if (num == j) continue;
                if ((i >> k) & 1) {
                    gg.push_front(k);
                    ans.push_back({1, k + 1});
                } else {
                    gg.push_back(k);
                    ans.push_back({2, k + 1});
                }
            }
        }
        if (fl) break;
        ans.clear();
    }
    if (ans.empty()) {
        cout << 0 << endl;
        return 0;
    }
    for (auto [i, j] : ans) {
        cout << i << " " << j << endl;
    }
    return 0;
}
