#include<bits/stdc++.h>

using namespace std;

const int INF = 2e9;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.rbegin(), a.rend());
    set<pair<int, int>> st;
    st.insert({INF, 0});
    for (int i = 0; i < n; ++i) {
        auto it = st.end();
        --it;
        auto [c, num] = *it;
        if (c - 2 >= a[i]) {
            st.erase(it);
            st.insert({a[i], num});
        } else {
            st.insert({a[i], (int)st.size()});
        }
    }
    cout << (int)st.size() << endl;
    return 0;
}
