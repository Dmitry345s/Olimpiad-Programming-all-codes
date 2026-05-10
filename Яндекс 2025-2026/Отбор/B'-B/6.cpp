#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> b(n);
    int ans = 0;
    for (int u = 30; u >= 0; --u) {
        vector<int> now;
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            if ((a[i] >> u) & 1) {
                now.push_back(b[i]);
            } else {
                now.push_back(b[i] + (1 << u) - a[i]);
            }
        }
        sort(now.begin(), now.end());
        for (int i = 0; i < k; ++i) {
            sum += now[i];
        }
        if (sum > m)  {
            for (int i = 0; i < n; ++i) {
                a[i] -= (((a[i] >> u) & 1) << u);
            }
            continue;
        }
        for (int i = 0; i < n; ++i) {
            if ((a[i] >> u) & 1) {
                a[i] -= (1 << u);
            } else {
                b[i] += (1 << u) - a[i];
                a[i] = 0;
            }
        }
        ans += (1 << u);
    }
    cout << ans << endl;
    return 0;
}
