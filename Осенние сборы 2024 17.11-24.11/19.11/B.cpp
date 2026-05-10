#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, q;
    cin >> n >> m >> q;
    vector<pair<int, int>> c(n);
    vector<int> rc(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i].first;
        c[i].second = i;
        rc[i] = c[i].first;
    }
    sort(c.rbegin(), c.rend());
    vector<int> p(n, 2 * n);
    for (int i = 0; i < n; ++i) {
        p[c[i].second] = i;
    }
    vector<pair<int, int>> st;
    for (int i = 2; i < n; ++i) {
        st.insert({-c[0].first - c[i].first, c[i].second});
    }
    vector<array<int, 3>> all;
    for (int i = 0; i < m; ++i) {

    }
    return 0;
}
