#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, q, y;
    cin >> n >> q >> y;
    vector<int> a(n);
    vector<int> ans(n, q);
    set<int> st;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        st.insert(i);
    }
    for (int i = 0; i < q; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        --l;
        if (x == 1) continue;
        auto it = st.lower_bound(l);
        while (it != st.end() && *it < r) {
            int u = *it;
            a[u] *= x;
            if (a[u] >= y) {
                ans[u] = i;
                st.erase(u);
            }
            it = st.lower_bound(u + 1);
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << q - ans[i] << " ";
    }
    cout << endl;
    return 0;
}
