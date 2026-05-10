#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i += 2) {
        for (int mask = 0; mask < (1 << n / 2); ++mask) {
            vector<int> b(n);
            b[i] = n;
            bool flag = true;
            int l = i, r = i;
            for (int bit = 0; bit < n / 2; ++bit) {
                int ch = (mask >> bit) & 1;
                if (ch && r == n - 1) {
                    flag = false;
                    break;
                }
                if (!ch && l == 0) {
                    flag = false;
                    break;
                }
                if (!ch) {
                    l -= 2;
                    b[l] = n - bit - 1;
                    b[l + 1] = n / 2 - bit;
                } else {
                    r += 2;
                    b[r] = n - bit - 1;
                    b[r - 1] = n / 2 - bit;
                }
            }
            for (int j = 0; j < n; ++j) {
                if (a[j] && a[j] != b[j]) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ans += 1;
            }
            for (int j = 0; j < n; ++j) {
                cout << b[j] << " ";
            }
            cout << endl;
        }
    }
    cout << ans << endl;
    return 0;
}
