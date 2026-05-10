#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> cnt(n);
    set<pair<int, int>> st;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            int b;
            cin >> b;
            --b;
            cnt[b] += 1;
            g[i].push_back(b);
        }
    }
    for (int i = 0; i < n; ++i) {
        st.insert({cnt[i], -i});
    }
    vector<int> topsort;
    while (!st.empty()) {
        int v = -(st.begin()->second);
        st.erase(st.begin());
        topsort.push_back(v);
        for (int to : g[v]) {
            st.erase({cnt[to], -to});
            cnt[to] -= 1;
            st.insert({cnt[to], -to});
        }
    }
    reverse(topsort.begin(), topsort.end());
    for (int i = 0; i < n; ++i) {
        cout << topsort[i] + 1 << " ";
    }
    return 0;
}
