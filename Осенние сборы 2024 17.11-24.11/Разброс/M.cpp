#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<string> st;
    for (int i = 0; i < n; ++i) {
        string now = "";
        now += s[i];
        st.push_back(now);
        if (i == n - 1) continue;
        now += s[i + 1];
        st.push_back(now);
    }
    sort(st.begin(), st.end());
    for (int i = 0; i < 26; ++i) {
        string ch = "";
        ch += (char)(97 + i);
        //cout << ch << endl;
        auto it = lower_bound(st.begin(), st.end(), ch);
        if (it == st.end() || *it != ch) {
            cout << ch << endl;
            return 0;
        }
    }
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            string ch = "";
            ch += (char)(97 + i);
            ch += (char)(97 + j);
            auto it = lower_bound(st.begin(), st.end(), ch);
            if (it == st.end() || *it != ch) {
                cout << ch << endl;
                return 0;
            }
        }
    }
    return 0;
}
