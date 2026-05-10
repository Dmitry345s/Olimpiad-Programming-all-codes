#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> all(m);
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        all[a[i]].push_back(i);
    }
    int cnt1 = k;
    set<pair<int, int>> st;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int t = lower_bound(all[a[i]].begin(), all[a[i]].end(), i) - all[a[i]].begin();
        if (st.find({-all[a[i]][t], a[i]}) != st.end()) {
            st.erase({-all[a[i]][t], a[i]});
            t++;
            if (t == (int)all[a[i]].size()) {
                cnt1++;
            } else {
                st.insert({-all[a[i]][t], a[i]});
            }
            continue;
        }
        //cout << a[i] << " " << (*st.begin()).first << " " << (*st.begin()).second << endl;
        ans++;
        if (cnt1 > 0) {
            cnt1--;
        } else {
            st.erase(st.begin());
        }
        if (i == all[a[i]].back()) {
            cnt1++;
        } else {
            int j = upper_bound(all[a[i]].begin(), all[a[i]].end(), i) - all[a[i]].begin();
            st.insert({-all[a[i]][j], a[i]});
        }
    }
    cout << ans << endl;
    return 0;
}
