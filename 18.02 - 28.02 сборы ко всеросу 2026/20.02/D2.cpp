#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    int sum1 = 0, sum2 = 0;
    vector<int> a(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i];
        sum1 += a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
        sum2 += b[i];
    }
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    //cout << sum1 << " " << sum2 << endl;
    if (sum1 >= sum2) {
        vector<int> pref(m + 1);
        for (int i = 0; i < m; ++i) {
            pref[i + 1] = pref[i] + b[i] - k;
        }
        int sufsum = -k * m;
        int ans = 2 * m;
        for (int i = m - 1; i >= 0; --i) {
            int l = -1, r = m + 1;
            while (l + 1 < r) {
                int c = (l + r) / 2;
                if (pref[c] > sufsum) {
                    l = c;
                } else {
                    r = c;
                }
            }
            //cout << i << " " << l << " " << r << endl;
            if (r < m + 1) ans = min(ans, r + m - i - 1);
            sufsum += a[i];
            l = -1;
            r = m + 1;
            while (l + 1 < r) {
                int c = (l + r) / 2;
                if (pref[c] > sufsum) {
                    l = c;
                } else {
                    r = c;
                }
            }
            if (r < m + 1) ans = min(ans, r + m - i);
        }
        cout << ans << endl;
    } else {
        vector<int> pref(m + 1);
        for (int i = 0; i < m; ++i) {
            pref[i + 1] = pref[i] + a[i] - k;
        }
        int sufsum = -k * m;
        int ans = 2 * m;
        for (int i = m - 1; i >= 0; --i) {
            int l = -1, r = m + 1;
            while (l + 1 < r) {
                int c = (l + r) / 2;
                if (pref[c] >= sufsum) {
                    l = c;
                } else {
                    r = c;
                }
            }
            if (r < m + 1) ans = min(ans, r + m - i - 1);
            sufsum += b[i];
            l = -1;
            r = m + 1;
            while (l + 1 < r) {
                int c = (l + r) / 2;
                if (pref[c] >= sufsum) {
                    l = c;
                } else {
                    r = c;
                }
            }
            if (r < m + 1) ans = min(ans, r + m - i);
        }
        cout << ans << endl;
    }
    return 0;
}
