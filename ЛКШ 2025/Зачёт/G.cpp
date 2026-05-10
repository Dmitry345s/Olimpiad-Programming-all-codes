#include<bits/stdc++.h>

using namespace std;

signed main() {
    int r;
    cin >> r;
    r--;
    string s;
    cin >> s;
    int n = (int)s.size();
    string t = s;
    sort(t.begin(), t.end());
    vector<pair<string, int>> st(n);
    vector<int> wh(n);
    for (int i = 0; i < n; ++i) {
        st[i].first.push_back(s[i]);
        st[i].first.push_back(t[i]);
        st[i].second = i;
    }
    sort(st.begin(), st.end());
    for (int i = 0; i < n; ++i) {
        wh[i] = st[i].second;
        //cout << st[i].first << " " << st[i].second << endl;
    }
    vector<int> p;
    int b = r;
    for (int i = 0; i < n; ++i) {
        p.push_back(wh[b]);
        b = wh[b];
    }
    for (int i = 0; i < n; ++i) {
        cout << s[p[i]];
    }
    cout << endl;
    return 0;
}
