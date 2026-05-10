#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        string s;
        cin >> s;
        string ans = "No";
        for (int i = 1; i < m; ++i) {
            if (s.substr(0, i) < s.substr(i, m - i)) {
                ans = "Yes";
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

