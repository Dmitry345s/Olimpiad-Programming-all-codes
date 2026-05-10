#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    string p, t;
    cin >> p >> t;
    string s = p + '#' + t + t;
    for (int d = -25; d < 26; ++d) {
        for (int i = 0; i < n; ++i) {
            s[i] = char(((int)p[i] - 97 + d + 26) % 26 + 97);
        }
        vector<int> z(s.size());
        z[0] = s.size();
        int l = 0, r = 1;
        for (int i = 1; i < (int)z.size(); ++i) {
            if (i <= r) {
                z[i] = min(z[i - l], r - i);
            }
            while (i + z[i] < (int)s.size() && s[z[i]] == s[z[i] + i]) {
                ++z[i];
            }
            if (i + z[i] > r) {
                r = i + z[i];
                l = i;
            }
            if (z[i] == n) {
                cout << "Success" << endl;
                cout << i - n - 1 << " " << d << endl;
                return 0;
            }
        }
    }
    cout << "Impossible" << endl;
}
