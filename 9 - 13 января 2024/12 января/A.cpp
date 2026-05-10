#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int cnt = 0;
    for (int i = 0; i < n - 1; ++i) {
        if (a[i] > a[i + 1]) {
            cnt++;
        }
    }
    for (int i = 0; i < m; ++i) {
        char t;
        cin >> t;
        if (t == '?') {
            if (cnt == 0) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        } else {
            int j, k;
            cin >> j >> k;
            --j;
            if (j - 1 >= 0 && a[j - 1] > a[j]) {
                cnt--;
            }
            if (j + 1 < n && a[j] > a[j + 1]) {
                cnt--;
            }
            a[j] = k;
            if (j - 1 >= 0 && a[j - 1] > a[j]) {
                cnt++;
            }
            if (j + 1 < n && a[j] > a[j + 1]) {
                cnt++;
            }
        }
    }
    return 0;
}
