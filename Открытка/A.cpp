#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    map<int, set<int>> mp;
    map<int, int> mp2;
    set<int> st, st3;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int ch = a[i] % m + 1;
        int ch2 = a[i] / m;
        //cout << ch2 << endl;
        mp[ch].insert(i);
        mp2[ch2]++;
        st.insert(ch);
        st3.insert(ch2);
    }
    int now = 0, u = 0;
    while (!st.empty()) {
        if (*(st3.rbegin()) - *(st3.begin()) + 1 == st3.size()) break;
        int f = *(st.begin());
        st.erase(st.begin());
        if (f >= u + m) {
            now = -1;
            break;
        }
        while (!mp[f].empty()) {
            int j = *(mp[f].begin());
            mp[f].erase(mp[f].begin());
            int ch2 = a[j] / m;
            mp2[ch2]--;
            if (mp2[ch2] == 0) {
                st3.erase(ch2);
            }
            mp2[ch2 - 1]++;
            st3.insert(ch2 - 1);
        }
        if (now == 0) {
            u = f;
        }
        now = f;
    }
    if (*(st3.rbegin()) - *(st3.begin()) + 1 == st3.size()) {
        cout << now << endl;
    } else {
        cout << -1 << endl;
    }
    return 0;
}
