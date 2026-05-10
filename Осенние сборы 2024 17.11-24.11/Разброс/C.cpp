#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> all;
    for (int i = 0; i < n; ++i) {
        int l, r;
        cin >> l >> r;
        all.push_back({l, -1});
        all.push_back({r, 1});
    }
    int now = 0;
    sort(all.begin(), all.end());
    if (all[0].first != 1 || all.back().first != m) {
        cout << "NO" << endl;
        return 0;
    }
    for (int i = 0; i < (int)all.size(); ++i) {
        if (now == 0 && i != 0) {
            cout << "NO" << endl;
            return 0;
        }
        now += all[i].second;
    }
    cout << "YES" << endl;
    return 0;
}
