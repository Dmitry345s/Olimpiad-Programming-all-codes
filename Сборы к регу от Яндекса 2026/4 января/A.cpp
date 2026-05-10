#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first;
        all[i].second = i;
    }
    sort(all.begin(), all.end());
    vector<int> ans;
    for (int i = n - 1; i >= n - k; --i) {
        ans.push_back(all[i].second);
    }
    reverse(all.begin(), all.end());
    while (all.back().first != all[0].first) all.pop_back();
    reverse(all.begin(), all.end());
    for (int u = 0; (int)ans.size() < m; ++u) {
        ans.push_back(all[u % (int)all.size()].second);
    }
    for (int v : ans) {
        cout << v + 1 << " ";
    }
    cout << endl;
    return 0;
}
