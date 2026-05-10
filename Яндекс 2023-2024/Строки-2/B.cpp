#include<bits/stdc++.h>

using namespace std;

signed main() {
    string p, t;
    cin >> p >> t;
    string s = p + '#' + t;
    vector<int> z(s.size());
    z[0] = s.size();
    int l = 0, r = 1;
    for (int i = 1; i < (int)s.size(); ++i) {
        if (i <= r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < (int)s.size() && s[z[i] + i] == s[z[i]]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = z[i] + i;
        }
    }
    reverse(p.begin(), p.end());
    reverse(t.begin(), t.end());
    string s2 = p + '#' + t;
    vector<int> z2(s2.size());
    z2[0] = s2.size();
    l = 0, r = 1;
    vector<int> ans;
    for (int i = 1; i < (int)s2.size(); ++i) {
        if (i <= r) {
            z2[i] = min(r - i, z2[i - l]);
        }
        while (i + z2[i] < (int)s2.size() && s2[z2[i] + i] == s2[z2[i]]) {
            ++z2[i];
        }
        if (i + z2[i] > r) {
            l = i;
            r = i + z2[i];
        }
        if (i < (int)p.size() + 1) continue;
        int j = ((int)t.size() - 1 - (i - (int)p.size() - 1)) + 2;
        if (z[j] + z2[i] >= (int)p.size() - 1 && j > (int)p.size()) {
            ans.push_back(j - (int)p.size());
        }
    }
    reverse(ans.begin(), ans.end());
    cout << ans.size() << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] << " ";
    }
}
