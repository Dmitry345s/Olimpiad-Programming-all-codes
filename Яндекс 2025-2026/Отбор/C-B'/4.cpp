#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int _;
    cin >> _;
    while (_--) {
        string s;
        cin >> s;
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int i = 0; i < (int)s.size(); ++i) {
            if (s[i] == '0') {
                if (l == 0) ans++;
                continue;
            }
            int now = 0;
            for (int j = i; j < (int)s.size(); ++j) {
                now *= 10;
                now += s[j] - '0';
                if (l <= now && now <= r) ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
