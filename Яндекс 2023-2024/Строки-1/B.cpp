#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<int> p(n);
    p[0] = 0;
    for (int i = 1; i < n; ++i) {
        int k = p[i - 1];
        while (k > 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[i] == s[k]) ++k;
        p[i] = k;
    }
    for (int i = 0; i < n; ++i) {
        cout << p[i] << " ";
    }
    return 0;
}
