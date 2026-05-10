#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    string t;
    cin >> t;
    if (t == "Alice") {
        int x;
        cin >> x;
        int u = 0;
        vector<int> ans;
        while (x > 0) {
            int p = x % 10;
            for (int i = 0; i < p; ++i) {
                ans.push_back(u);
            }
            x /= 10;
            ++u;
        }
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i];
        }
        cout << endl;
    } else {
        string b;
        cin >> b;
        vector<int> ch(10);
        for (int i = 0; i < (int)b.size(); ++i) {
            ch[b[i] - '0'] += 1;
        }
        int ans = 0;
        int now = 1;
        for (int i = 0; i < 10; ++i) {
            ans += ch[i] * now;
            now *= 10;
        }
        cout << ans << endl;
    }
    return 0;
}
