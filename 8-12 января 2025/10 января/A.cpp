#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    set<pair<int, int>> st;
    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        st.insert({x, i});
    }
    vector<int> ans(n);
    for (int i = n - 1; i >= 0; --i) {
        auto it = st.lower_bound({a[i], -1});
        if (it == st.end()) {
            ans[i] = -2;
        } else {
            ans[i] = (*it).second;
            st.erase(it);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << endl;
    }
    return 0;
}
