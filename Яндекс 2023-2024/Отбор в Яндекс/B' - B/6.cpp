#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<int> c;
        int ans = 0;
        int dif = 0;
        for (int i = 0; i < n; ++i) {
            int a, b;
            cin >> a >> b;
            ans += max(a, b);
            if (a < b) {
                c.push_back(b - a);
            } else {
                dif = a - b;
            }
        }
        sort(c.begin(), c.end());
        if (c.size() == 0 && n == 1) {
            cout << ans - dif << endl;
            continue;
        }
        if (c.size() == n - 1) {
            if (2 * n - 1 <= m) {
                ans = max(ans - dif, ans - c[0]);
            } else {
                int y = 2 * n - m - (n - c.size());
                for (int i = 0; i < min(y, (long long)c.size()); ++i) {
                    ans -= c[i];
                }
            }
            cout << ans << endl;
            continue;
        }
        if (c.size() == n) {
            if (2 * n - 1 <= m) {
                ans = ans;
            } else {
                int y = 2 * n - m - (n - c.size());
                for (int i = 0; i < min(y, (long long)c.size()); ++i) {
                    ans -= c[i];
                }
            }
            cout << ans << endl;
            continue;
        }
        int y = 2 * n - m - (n - c.size());
        for (int i = 0; i < min(y, (long long)c.size()); ++i) {
            ans -= c[i];
        }
        cout << ans << endl;
    }
    return 0;
}

