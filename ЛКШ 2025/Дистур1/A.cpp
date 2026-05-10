#include<bits/stdc++.h>

using namespace std;
using ll = long long;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> cnt(n);
    set<pair<int, int>> now;
    multiset<int> st;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        cnt[v]++;
        now.insert({u, v});
    }
    for (int i = 0; i < n; ++i) {
        st.insert(-cnt[i]);
    }
    if (-*st.begin() < 2) {
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
        st.erase(st.find(-cnt[b]));
        st.erase(st.find(-cnt[a]));
        if (now.find({a, b}) == now.end()) {
            now.erase({b, a});
            now.insert({a, b});
            cnt[a]--;
            cnt[b]++;
        } else {
            now.insert({b, a});
            now.erase({a, b});
            cnt[a]++;
            cnt[b]--;
        }
        st.insert(-cnt[b]);
        st.insert(-cnt[a]);
        if (-*st.begin() < 2) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
