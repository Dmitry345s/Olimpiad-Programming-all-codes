#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    set<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < n; ++i) {
        st.insert({a[i], i});
    }
    int ans = 0;
    vector<int> used(n);
    for (int i = 0; i < n; ++i) {
        if (used[i]) continue;
        used[i] = 1;
        st.erase({a[i], i});
        int x = a[i] + 1;
        auto it = st.upper_bound({x, -1});
        if (it != st.end() && (*it).first == x) {
            used[(*it).second] = 1;
            st.erase(it);
        }
        ans += 1;
    }
    cout << ans << endl;
    return 0;
}
