#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    int n;
    cin >> n;
    for (int i = 0; i < (n + 2) / 3; ++i) {
        string t;
        cin >> t;
        s += t;
    }
    int i = 0;
    string ans;
    while (i + 3 < n) {
        if (s[i] == s[i + 1] && s[i + 1] == s[i + 2]) {
            ans.push_back(s[i]);
            ans.push_back(s[i + 1]);
            ans.push_back(s[i + 2]);
            i += 3;
        } else {
            i++;
        }
    }
    if (i + 3 <= n && s[i] == s[i + 1] && s[i + 1] == s[i + 2]) {
        ans.push_back(s[i]);
        ans.push_back(s[i + 1]);
        ans.push_back(s[i + 2]);
    } else if (i + 3 <= n && s[i] == s[i + 1]) {
        ans.push_back(s[i]);
        ans.push_back(s[i + 1]);
    } else if (i + 3 <= n && s[i + 1] == s[i + 2]) {
        ans.push_back(s[i + 1]);
        ans.push_back(s[i + 2]);
    } else if (i + 2 <= n && s[i] == s[i + 1]) {
        ans.push_back(s[i]);
        ans.push_back(s[i + 1]);
    } else {
        ans.push_back(s[i]);
    }
    cout << (int)ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); i += 3) {
        cout << ans[i] << ans[i + 1] << ans[i + 2] << endl;
    }
    return 0;
}

