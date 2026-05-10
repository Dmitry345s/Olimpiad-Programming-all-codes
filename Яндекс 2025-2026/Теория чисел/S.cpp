#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    int mn = 2e9;
    map<int, int> all;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        mn = min(a[i], mn);
        for (int j = 1; j * j <= a[i]; ++j) {
            if (a[i] % j == 0) {
                all[j] = __gcd(all[j], a[i]);
                all[a[i] / j] = __gcd(all[a[i] / j], a[i]);
            }
        }
    }
    int ans = 0;
    for (auto [key, val] : all) {
        if (val <= mn && val == key) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
