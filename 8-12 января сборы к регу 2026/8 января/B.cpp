#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    vector<int> ans2(n);
    set<pair<int, int>> all;
    for (int i = 0; i < m; ++i) {
        all.insert({-1, i});
    }
    for (int i = 0; i < n; ++i) {
        auto it = all.upper_bound({a[i], n});
        --it;
        auto [v, in] = *it;
        all.erase(it);
        ans2[a[i]] = in;
        all.insert({a[i], in});
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[i] = ans2[a[i]];
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans2[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}

