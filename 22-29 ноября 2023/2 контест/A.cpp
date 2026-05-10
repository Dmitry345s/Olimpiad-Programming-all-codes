#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, t;
    cin >> n >> t;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    multiset<int> st;
    int now = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        while (st.size() > 0 && now + a[i].first > t) {
            auto it = --st.end();
            now -= *it;
            st.erase(it);
        }
        if (now + a[i].first + a[i].second <= t) {
            st.insert(a[i].second);
            now += a[i].second;
        } else if (st.size() > 0) {
            auto it = st.end();
            --it;
            if (*it > a[i].second) {
                now = now - *it + a[i].second;
                st.erase(it);
                st.insert(a[i].second);
            }
        }
        ans = max(ans, (int)st.size());
    }
    cout << ans << endl;
    return 0;
}
