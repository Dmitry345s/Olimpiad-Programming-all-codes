#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> all(n);
    vector<pair<int, int>> cls;
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        all[i].assign(c, 0);
        for (int j = 0; j < c; ++j) {
            cin >> all[i][j];
        }
        sort(all[i].begin(), all[i].end());
        cls.push_back({all[i][0], all[i].back()});
    }
    sort(cls.begin(), cls.end());
    set<pair<int, int>> st;
    int ans = 2e9;
    for (int i = n - 1; i >= 0; --i) {
        //cout << cls[i].first << " " << cls[i].second << endl;
        if (st.size() < k) {
            st.insert({cls[i].second, i});
        } else {
            auto it = st.end();
            --it;
            if ((*it).first > cls[i].second) {
                st.erase(it);
                st.insert({cls[i].second, i});
            }
        }
        if (st.size() >= k) {
            auto it = st.end();
            --it;
            ans = min(ans, (*it).first - cls[i].first);
        }
    }
    cout << ans << endl;
    return 0;
}
