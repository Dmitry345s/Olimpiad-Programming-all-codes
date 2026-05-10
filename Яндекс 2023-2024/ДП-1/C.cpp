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
    pref[0] = 0;
    for (int i = 1; i <= n; ++i) {
        pref[i] = pref[i - 1] + a[i - 1];
    }
    vector<int> bag(x + 1, 1e9);
    bag[0] = 0;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= x; ++j) {
            if (j < pref[i]) continue;
            bag[j] = min(bag[j], bag[j - pref[i]] + i + 1);
        }
    }
    for (int j = 0; j <= x; ++j) {
        if (j < pref[n]) continue;
        if (bag[j] >= bag[j - pref[n]] + n + 1) {
            bag[j] = bag[j - pref[n]] + n + 1;
        }
    }
    for (int j = 0; j <= x; ++j) {
        if (j < pref[n]) continue;
        if ((x - j) % a.back() != 0) continue;
        if (bag[x] >= bag[j - pref[n]] + n + 1 + (x - j) / a.back()) {
            bag[x] = bag[j - pref[n]] + n + 1 + (x - j) / a.back();
        }
    }
    if (bag[x] == (int)1e9) {
        cout << -1 << endl;
        return 0;
    }
    cout << bag[x] - 1 << endl;
    return 0;
}
