#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, c;
    cin >> n >> c;
    vector<int> a(n);
    vector<int> used(n, 0);
    vector<int> del(n);
    set<pair<int, int>> st;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (i == 0) {
            del[i] = c;
        }
        st.insert({-(del[i] + a[i]), i});
    }
    int l = 0;
    vector<int> ans(n);
    int cnt = 0;
    while (!st.empty()) {
        int v = st.begin()->second;
        //cout << v << endl;
        st.erase(st.begin());
        ans[v] = cnt;
        cnt++;
        used[v] = 1;
        while (l < n && used[l] == 1) {
            //cout << l << endl;
            ++l;
        }
        if (l == n) continue;
        int del2 = a[v];
        del2 += del[v];
        del[v] = 0;
        st.erase({-(del[l] + a[l]), l});
        del[l] = del2;
        st.insert({-(del[l] + a[l]), l});
    }
    for (int i = 0; i < n; ++i) {
        if (i == 0) {
            st.insert({-(c + a[i]), i});
        } else {
            st.insert({-a[i], i});
        }
    }
    int nowd = c;
    for (int i = 0; i < n; ++i) {
        int v = st.begin()->second;
        ans[v] = min(ans[v], i);
        if (i == n - 1) continue;
        st.erase({-(nowd + a[i]), i});
        nowd += a[i];
        st.erase({-a[i + 1], i});
        st.insert({-(nowd + a[i + 1]), i + 1});
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
