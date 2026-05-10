#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    set<pair<int, int>> st, st2;
    int n;
    cin >> n;
    st.insert({1e5, 1});
    st2.insert({1, 1e5});
    map<string, pair<int, int>> mp;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        if (s[4] == '=') {
            int l = 12;
            int x = 0;
            while(s[l] != ')') {
                x *= 10;
                x += s[l] - '0';
                l++;
            }
            string t;
            for (int u = 0; u < 4; ++u) {
                t.push_back(s[u]);
            }
            auto it = st2.begin();
            while (it != st2.end() && (*it).second < x) {
                ++it;
            }
            if (it == st2.end()) {
                mp[t] = {0, x};
                continue;
            }
            auto [sr, num] = (*it);
            auto it2 = st.lower_bound({(*it).second, (*it).first});
            mp[t] = {sr, x};
            num -= x;
            sr += x;
            st.erase(it2);
            st2.erase(it);
            if (num != 0) {
                st.insert({num, sr});
                st2.insert({sr, num});
            }
        } else if (s[0] == 'p') {
            string t;
            for (int u = 6; u < 10; ++u) {
                t.push_back(s[u]);
            }
            cout << mp[t].first << endl;
        } else {
            string t;
            for (int u = 5; u < 9; ++u) {
                t.push_back(s[u]);
            }
            auto [sr, x] = mp[t];
            if (sr == 0) continue;
            auto it = st2.upper_bound({sr, 0});
            auto it2 = it;
            if (it2 != st2.begin()) {
                --it2;
            }
            mp[t] = {0, x};
            int flag1 = 0, flag2 = 0;
            if (it != st2.end() && (*it).first == sr + x) {
                auto [sr2, x2] = *it;
                auto it3 = st.lower_bound({x2, sr2});
                st.erase(it3);
                flag1 = 1;
                x += x2;
            }
            if (it2 != st2.end() && (*it2).first < sr && (*it2).first + (*it2).second == sr) {
                auto [sr2, x2] = *it2;
                auto it3 = st.lower_bound({x2, sr2});
                st.erase(it3);
                flag2 = 1;
                x += x2;
                sr = sr2;
            }
            if (flag1) st2.erase(it);
            if (flag2) st2.erase(it2);
            st.insert({x, sr});
            st2.insert({sr, x});
        }
    }
    return 0;
}
