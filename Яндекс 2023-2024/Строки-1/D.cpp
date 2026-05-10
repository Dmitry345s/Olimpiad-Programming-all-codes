#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s, t;
    cin >> s >> t;
    s = s + '#' + t + t;
    int n = t.size();
    int ans = -1;
    vector<int> z(s.size());
    z[0] = s.size();
    int l = 0, r = 1;
    for (int i = 1; i < z.size(); ++i) {
        if (i <= r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < z.size() && s[z[i]] == s[z[i]+ i]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = z[i] + i;
        }
        if (z[i] == n) {
            ans = i - n - 1;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
