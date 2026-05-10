#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    int MAX = 1e6;
    unordered_set<int> st;
    vector<pair<int, vector<int>>> zs(MAX);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        st.insert(a);
        zs[a].second.push_back(i);
    }
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int x;
            cin >> x;
            for (auto val : st) {
                if (val + zs[val].first == x) {
                    zs[val].first += 1;
                }
            }
        } else {
            int l, r, y;
            cin >> l >> r >> y;
            l--;
            r--;
            int ans = 0;
            for (auto val : st) {
                if (val + zs[val].first <= y) continue;
                ans += (upper_bound(zs[val].second.begin(), zs[val].second.end(), r) - zs[val].second.begin());
                ans -= (lower_bound(zs[val].second.begin(), zs[val].second.end(), l) - zs[val].second.begin());
            }
            ans = (r - l + 1) - ans;
            cout << ans << '\n';
        }
    }
    return 0;
}
