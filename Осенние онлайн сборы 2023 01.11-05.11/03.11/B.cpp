#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    vector<int> b(n), b2(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        b[i] = (i % 2) * k;
        b2[i] = (!(i % 2)) * k;
    }
    vector<int> mn, pl;
    int mn1 = 0, pl1 = 0, z1 = 0;
    for (int i = 0; i < n; ++i) {
        if (b[i] - a[i] > 0) {
            pl1 += 1;
            pl.push_back(b[i] - a[i]);
        } else if (b[i] - a[i] < 0) {
            mn1 += 1;
            mn.push_back(a[i] - b[i]);
        } else {
            z1 += 1;
        }
    }
    sort(mn.begin(), mn.end());
    sort(pl.begin(), pl.end());
    int del = 0;
    if (pl1 > mn1 + z1) {
        del = pl[(pl1 - mn1 - z1) / 2];
    } else if (mn1 > pl1 + z1) {
        del = -mn[(mn1 - pl1 - z1) / 2];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x = abs((b[i] - del) - a[i]);
        ans += x;
    }
    vector<int> mn2, pl2;
    int mn3 = 0, pl3 = 0, z3 = 0;
    for (int i = 0; i < n; ++i) {
        if (b2[i] - a[i] > 0) {
            pl3 += 1;
            pl2.push_back(b2[i] - a[i]);
        } else if (b2[i] - a[i] < 0) {
            mn3 += 1;
            mn2.push_back(a[i] - b2[i]);
        } else {
            z3 += 1;
        }
    }
    sort(mn2.begin(), mn2.end());
    sort(pl2.begin(), pl2.end());
    int del2 = 0;
    if (pl3 > mn3 + z3) {
        del2 = pl2[(pl3 - mn3 - z3) / 2];
    } else if (mn3 > pl3 + z3) {
        del2 = -mn2[(mn3 - pl3 - z3) / 2];
    }
    int ans2 = 0;
    for (int i = 0; i < n; ++i) {
        int x = abs((b2[i] - del2) - a[i]);
        ans2 += x;
    }
    cout << min(ans, ans2) << endl;
    return 0;
}
