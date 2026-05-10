#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> z(n);
    z[0] = n;
    int l = 0, r = 1;
    for (int i = 1; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (z[i] + i < n && s[z[i]] == s[z[i] + i]) {
            ++z[i];
        }
        if (i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << z[i] << " ";
    }
}
