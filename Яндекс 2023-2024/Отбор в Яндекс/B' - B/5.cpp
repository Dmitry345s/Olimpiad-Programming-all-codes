#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    int maxm = 0;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'N') {
            maxm = max(maxm, i);
            break;
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == 'N') {
            maxm = max(maxm, n - i - 1);
            break;
        }
    }
    int r = (n + 1) / 2;
    char ch = s[n / 2];
    while (r < n && s[n - r - 1] == ch && s[r] == ch) {
        r++;
    }
    cout << max(maxm, r) << endl;
    return 0;
}
