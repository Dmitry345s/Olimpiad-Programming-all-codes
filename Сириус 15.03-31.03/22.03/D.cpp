#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m), x(n), y(m);
    vector<int> ch2(n + m + 1, -1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        ch2[b[i]] = i;
    }
    vector<int> pref(m + 1);
    pref[0] = 0;
    for (int i = 0; i < m; ++i) {
        cin >> y[i];
        pref[i + 1] = pref[i] + y[i];
    }
    int ans = 0;
    pair<int, int> ans1, ans2;
    for (int l = 0; l < n; ++l) {
        vector<int> ch(n + m + 1);
        set<int> st = {-1, m};
        set<pair<int, int>> st2 = {{pref[m], 0}};
        int sum = 0;
        int mx = pref[m];
        pair<int, int> now = {1, m};
        for (int r = l; r < n; ++r) {
            ch[a[r]] = 1;
            sum += x[r];
            if (ch2[a[r]] != -1) {
                auto it = st.upper_bound(ch2[a[r]]);
                int sum1 = pref[(*it)] - pref[ch2[a[r]] + 1];
                int right1 = (*it);
                --it;
                int sum2 = pref[ch2[a[r]]] - pref[(*it) + 1];
                int left1 = (*it) + 1;
                st2.erase({pref[right1] - pref[left1], left1});
                st2.insert({sum1, ch2[a[r]] + 1});
                st2.insert({sum2, left1});
                st.insert(ch2[a[r]]);
            }
            auto it = st2.end();
            --it;
            int sum2 = (*it).first;
            if (sum2 + sum >= ans) {
                ans = sum + sum2;
                ans1 = {l + 1, r + 1};
                ans2 = {(*it).second + 1, (*(st.upper_bound((*it).second)))};
            }
        }
    }
    for (int l = 0; l < m; ++l) {
        int st = 0;
        for (int r = l; r < m; ++r) {
            st += y[r];
            if (st >= ans) {
                ans = st;
                ans1 = {0, 0};
                ans2 = {l + 1, r + 1};
            }
        }
    }
    for (int l = 0; l < n; ++l) {
        int st = 0;
        for (int r = l; r < n; ++r) {
            st += x[r];
            if (st >= ans) {
                ans = st;
                ans1 = {l + 1, r + 1};
                ans2 = {0, 0};
            }
        }
    }
    cout << ans << endl;
    cout << ans1.first << " " << ans1.second << endl;
    cout << ans2.first << " " << ans2.second << endl;
    return 0;
}
