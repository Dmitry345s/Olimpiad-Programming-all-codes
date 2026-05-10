#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    string t = s;
    reverse(t.begin(), t.end());
    s = s + '#' + t;
    vector<int> z(s.size());
    vector<int> a(n);
    int l = 0, r = 1;
    for (int i = 1; i < z.size(); ++i) {
        if (i <= r) {
            z[i] = min(r - i, z[i - l]);
        }
        while (i + z[i] < z.size() && s[z[i]] == s[z[i] + i]) {
            ++z[i];
        }
        if (z[i] + i > r) {
            l = i;
            r = z[i] + i;
        }
        if (i > n) {
            int j = i - n - 1;
            a[n - j - 1] = z[i];
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << a[i] << " ";
    }
    return 0;
}
