#include<bits/stdc++.h>

using namespace std;

signed main() {
    string t;
    cin >> t;
    if (t == "Alice") {
        long long x;
        cin >> x;
        if (x == 0) {
            cout << '0' << endl;
            return 0;
        }
        string ans;
        int ch = 9;
        while (x != 0) {
            int y = x % 10;
            x /= 10;
            for (int i = 0; i < y; ++i) {
                ans.push_back(char(ch + int('0')));
            }
            ch--;
        }
        reverse(ans.begin(), ans.end());
        cout << ans << endl;
    } else {
        string p;
        cin >> p;
        if (p == "0") {
            cout << 0 << endl;
            return 0;
        }
        sort(p.rbegin(), p.rend());
        int i = 0;
        int ch = 9;
        long long ans = 0;
        long long ps = 1;
        while (i < (int)p.size()) {
            int cnt = 0;
            while (i < (int)p.size() && p[i] - '0' == ch) {
                cnt++;
                ++i;
            }
            ans += ps * cnt;
            --ch;
            ps *= 10;
        }
        cout << ans << endl;
    }
    return 0;
}
