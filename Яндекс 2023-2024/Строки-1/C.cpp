#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s, t;
    cin >> s >> t;
    s = t + '#' + s;
    int n = t.size();
    vector<int> z(s.size());
    z[0] = s.size();
    int l = 0, r = 1;
    for (int i = 1; i < z.size(); ++i) {
        if (i <= r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < z.size() && s[z[i]] == s[z[i] + i]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = z[i] + i;
        }
        if (z[i] == n) {
            cout << i - n - 1 << " ";
        }
    }
    return 0;
}
