#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        ans = max(ans, 1ll * a[i]);
    }
    sort(a.begin(), a.end());
    map<int, long long> mp;
    for (int i = 0; i < n; ++i) {
        long long cnt = 1;
        while (a[i] % 2 == 0) {
            a[i] /= 2;
            cnt *= 2;
        }
        mp[a[i]] += cnt;
    }
    for (auto [key, val] : mp) {
        long long check = key;
        while (val != 1) {
            val /= 2;
            check *= 2;
        }
        ans = max(ans, check);
    }
    cout << ans << endl;
    return 0;
}
