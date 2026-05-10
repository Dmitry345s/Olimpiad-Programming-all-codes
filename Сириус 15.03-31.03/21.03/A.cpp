#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k, l, r;
    cin >> n >> k >> l >> r;
    vector<int> a(n);
    vector<pair<int, int>> b;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b.push_back({a[i], i});
    }
    sort(b.begin(), b.end());
    int rl = 0, rr = 0;
    set<int> st;
    for (int i = 0; i < n; ++i) {
        //cout << i << endl;
        while (rr < n && b[rr].first - b[i].first <= r) {
            st.insert(b[rr].second);
            rr++;
        }
        while (rl < n && b[rl].first - b[i].first < l) {
            st.erase(b[rl].second);
            rl++;
        }
        auto it = st.upper_bound(b[i].second);
        if (it != st.end() && abs((*it) - b[i].second) <= k) {
            cout << b[i].second + 1 << " " << (*it) + 1 << endl;
            return 0;
        }
        it = st.lower_bound(b[i].second);
        if (it != st.begin()) {
            --it;
            if (b[i].second - (*it) <= k) {
                cout << (*it) + 1 << " " << b[i].second + 1 << endl;
                return 0;
            }
        }
    }
    cout << -1 << " " << -1 << endl;
    return 0;
}
