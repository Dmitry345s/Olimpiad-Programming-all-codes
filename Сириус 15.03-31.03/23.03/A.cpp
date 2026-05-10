#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k, c, d;
    cin >> n >> k >> c >> d;
    vector<int> a(n), b(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i];
        sum += (b[i] - a[i]) * d;
    }
    vector<int> p;
    vector<int> pref(n);
    for (int i = 0; i < n - 1; ++i) {
        p.push_back(a[i + 1] - b[i]);
    }
    sort(p.begin(), p.end());
    for (int i = 0; i < n - 1; ++i) {
        pref[i + 1] = pref[i] + p[i];
    }
    int ans = 1e18;
    for (int i = 1; i <= n; ++i) {
        int nans = sum + (i - 1) * c;
        int j = n - i * k;
        if (j >= 0) {
            nans += pref[j] * d;
        }
        ans = min(ans, nans);
    }
    cout << ans << endl;
    return 0;
}
