#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int t = 0;
    while (true) {
        t++;
        if (t % 2 == 1) {
            int j;
            cin >> j;
            --j;
            if (a[j] == 1) {
                cout << 1 << endl;
                a[j] = 0;
                continue;
            }
            int cnt1 = 0, cnt2 = 0;
            for (int i = 0; i < n; ++i) {
                if (a[i] == 1) {
                    cnt1++;
                } else if (a[i] > 1) {
                    cnt2++;
                }
            }
            if (cnt2 > 1) {
                cout << a[j] - 1 << endl;
                a[j] = 1;
                continue;
            }
            if (cnt1 % 2 == 0) {
                cout << a[j] << endl;
                a[j] = 0;
                continue;
            }
            cout << a[j] - 1 << endl;
            a[j] = 1;
        } else {
            int ans = -1;
            for (int i = 0; i < n; ++i) {
                if (a[i] == 1) {
                    ans = i + 1;
                }
            }
            cout << ans << endl;
            if (ans == -1) return 0;
            int u;
            cin >> u;
            a[ans - 1] -= u;
        }
    }
    return 0;
}
