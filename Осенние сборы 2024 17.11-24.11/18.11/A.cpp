#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    set<pair<int, int>> st;
    vector<int> cnt(n);
    int ans = n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (cnt[b] == 0) {
            ans--;
        }
        cnt[b]++;
        st.insert({a, b});
    }
    if (ans == 1) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        if (st.find({a, b}) == st.end()) {
            swap(a, b);
        }
        if (cnt[a] == 0) {
            ans--;
        }
        if (cnt[b] == 1) {
            ans++;
        }
        cnt[a]++;
        cnt[b]--;
        st.erase({a, b});
        st.insert({b, a});
        if (ans == 1) {
            cout << "YES" << '\n';
        } else {
            cout << "NO" << '\n';
        }
    }
    return 0;
}
