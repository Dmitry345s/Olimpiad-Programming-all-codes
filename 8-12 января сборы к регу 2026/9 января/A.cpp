#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    string s;
    cin >> s;
    int n = (int)s.size();
    int ans = 0;
    vector<int> prev(n, -1);
    for (int i = 1; i < (int)s.size(); ++i) {
        prev[i] = prev[i - 1];
        if (s[i - 1] == 'S') {
            prev[i] = i - 1;
        }
    }
    int ls = n;
    for (int i = n - 1; i >= 0; --i) {
        if (i != n - 1 && s[i + 1] == 'S') {
            ls = i + 1;
        }
        //cout << i << " " << ls << " " << prev[i] << endl;
        if (s[i] == 'S') ans += (ls - i) * (i - prev[i]);
    }
    prev.assign(n, -1);
    for (int i = 1; i < (int)s.size(); ++i) {
        prev[i] = prev[i - 1];
        if (s[i - 1] == 'U') {
            prev[i] = i - 1;
        }
    }
    ls = n;
    for (int i = n - 1; i >= 0; --i) {
        if (i != n - 1 && s[i + 1] == 'U') {
            ls = i + 1;
        }
        //cout << i << " " << ls << " " << prev[i] << endl;
        if (s[i] == 'U') ans += (ls - i) * (i - prev[i]);
    }
    for (int i = 0; i < n - 1; ++i) {
        if (s[i] != s[i + 1]) {
            ans -= 2;
        }
    }
    cout << ans - n << endl;
    return 0;
}
