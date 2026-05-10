#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }
    vector<int> mx(n + 1);
    mx[0] = 0;
    for (int i = 0; i < n; ++i) {
        mx[i + 1] = max(mx[i], pref[i + 1]);
    }
    if (pref.back() < 0) {
        cout << -1 << endl;
        return 0;
    }
    int now = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (pref[i + 1] + now < 0) {
            int x = abs(pref[i + 1] + now);
            if (mx[i] <= 0) {
                ans = -1;
                break;
            }
            int y = (x + mx[i] - 1) / mx[i];
            now += y * mx[i];
            ans += y;
        }
        now += pref[i + 1];
        ans += 1;
    }
    if (ans <= 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}

