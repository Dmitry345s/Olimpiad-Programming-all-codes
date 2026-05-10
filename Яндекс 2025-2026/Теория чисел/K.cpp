#include<bits/stdc++.h>

using namespace std;

signed main() {
    string s;
    cin >> s;
    int n = (int)s.size();
    vector<int> bef(n);
    vector<int> af(n + 1);
    bef[0] = 0;
    for (int i = 1; i < n; ++i) {
        bef[i] = bef[i - 1];
        if (s[i] == '0') {
            bef[i] = i;
        }
    }
    af[n] = 2 * n + 1;
    for (int i = n - 1; i >= 0; --i) {
        af[i] = af[i + 1];
        if (s[i] == '1') {
            af[i] = i;
        }
    }
    int ansa = -1, ansb = -1;
    int nowans = -1;
    for (int x = 1; x <= n; ++x) {
        int mn = n + 1, mx = -1;
        int now = x;
        for (; now <= n; now += x) {
            mx = max(bef[now - 1] - now + x, mx);
            mn = min(af[now - x] - now + x, mn);
        }
        if (now - x < n) {
            mx = max(bef[n - 1] - now + x, mx);
            mn = min(af[now - x] - now + x, mn);
        }
        if (mn > mx && nowans < n / x * (x - mx - 1) + max(0, n % x - mx - 1)) {
            ansa = mx + 1;
            ansb = x - ansa;
            nowans = n / x * (x - mx - 1) + max(0, n % x - mx - 1);
        }
    }
    if (ansa == -1) {
        cout << -1 << endl;
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        int u = i % (ansa + ansb);
        if (u < ansa) {
            cout << 0;
        } else {
            cout << 1;
        }
    }
    return 0;
}
