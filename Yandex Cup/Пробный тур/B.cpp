#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n;
        cin >> n;
        vector<int> h(n);
        for (int i = 0; i < n; ++i) {
            cin >> h[i];
        }
        int ls = 0;
        vector<int> pref(n);
        for (int i = 1; i < n; ++i) {
            if (h[i - 1] >= h[i]) {
                ls = i;
            }
            pref[i] = i - ls;
        }
        ls = n - 1;
        vector<int> suf(n);
        for (int i = n - 2; i >= 0; --i) {
            if (h[i + 1] >= h[i]) {
                ls = i;
            }
            suf[i] = ls - i;
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            ans += suf[i] * pref[i];
        }
        cout << ans << endl;
    }
    return 0;
}
