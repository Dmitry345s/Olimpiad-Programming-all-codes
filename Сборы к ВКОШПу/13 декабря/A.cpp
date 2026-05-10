#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int cur_max = -1;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > cur_max) {
            if (i == n - 1 || a[i] > a[i + 1]) {
                ans++;
            }
            cur_max = a[i];
        }
    }
    cout << ans << endl;
}
