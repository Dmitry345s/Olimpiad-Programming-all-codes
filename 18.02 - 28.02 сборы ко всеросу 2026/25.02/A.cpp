#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    int ans = n + 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        ans += b[i] + 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        __int128 u = (__int128)a[i] * b[i + 1] * a[i + 1] * b[i] / __gcd(a[i] * b[i + 1], a[i + 1] * b[i]);
        __int128 y = min((__int128)a[i] * b[i + 1] * b[i], (__int128)a[i + 1] * b[i] * b[i + 1]) / u + 1;
        ans -= y;
    }
    cout << ans << endl;
    return 0;
}
