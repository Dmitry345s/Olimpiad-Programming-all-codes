#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> pref(n + 1);
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + (a[i - 1] >= x);
    }
    int m;
    cin >> m;
    int now = 0;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int a;
            cin >> a;
            pref.push_back(pref.back() + (a >= x));
        } else if (t == 2) {
            now += 1;
        } else {
            int j;
            cin >> j;
            j += now;
            cout << pref[j] - pref[now] << endl;
        }
    }
    return 0;
}
