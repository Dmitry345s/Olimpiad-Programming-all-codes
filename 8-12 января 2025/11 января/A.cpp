#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, l;
    cin >> n >> l;
    vector<int> ch(2 * l - 1);
    vector<vector<int>> ch2(l);
    for (int i = 0; i < l; ++i) {
        ch[i] = i;
        ch2[i].push_back(i);
    }
    for (int i = 1; i < l - 1; ++i) {
        ch[l - 1 + i] = l - 1 - i;
        ch2[l - 1 - i].push_back(l - 1 + i);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int r, s, t;
        cin >> r >> s >> t;
        s--;
        int s2 = s + t;
        --r;
        if (t >= 2 * l - 2) {
            ans++;
            continue;
        }
        s %= (2 * l - 2);
        int flag = 0;
        int u = (s + t) % (2 * l - 2);
        for (int x : ch2[r]) {
            //cout << x << " ";
            if (u >= s) {
                if (s <= x && x < u) {
                    flag = 1;
                }
            } else {
                if (!(u <= x && x < s)) {
                    flag = 1;
                }
            }
        }
        /*for (int j = s; j < s + t; ++j) {
            int x = j % (2 * l - 2);
            if (ch[x] == r) flag = 1;
        }*/
        //cout << flag << endl;
        ans += flag;
    }
    cout << ans << endl;
    return 0;
}
