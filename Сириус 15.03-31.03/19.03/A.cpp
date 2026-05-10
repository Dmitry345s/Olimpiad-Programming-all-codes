#include<bits/stdc++.h>

#define int long long

using namespace std;

int get (string s, int ch) {
    if (s.size() == 1) {
        int ans = (s[0] - '0');
        if (ch == 0) {
            ans -= 1;
        }
        return ans;
    }
    int ans = 9 * 10 * ((int)s.size() - 2) + 9;
    for (int i = 1; i < 10; ++i) {
        if (i > s[0] - '0') break;
        for (int j = 0; j < 10; ++j) {
            int flag = 1;
            int flag2 = 1;
            int last = i;
            if (i < s[0] - '0') {
                flag2 = 0;
            }
            for (int l = 1; l < (int)s.size(); ++l) {
                last = (last + j) % 10;
                if (flag2 && last > s[l] - '0') {
                    flag = 0;
                    break;
                }
                if (last < s[l] - '0') {
                    flag2 = 0;
                }
            }
            if (flag && flag2 && ch == 0) {
                ans--;
            }
            ans += flag;
        }
    }
    return ans;
}

signed main() {
    string l, r;
    cin >> l >> r;
    //cout << get(r, -1) << " " << get(l, 0) << endl;
    cout << get(r, -1) - get(l, 0) << endl;
    return 0;
}
