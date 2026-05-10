#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int x, y, a, b, c;
    cin >> x >> y >> a >> b >> c;
    vector<int> k(a), k2(b), k3(c);
    for (int i = 0; i < a; ++i) {
        cin >> k[i];
    }
    for (int i = 0; i < b; ++i) {
        cin >> k2[i];
    }
    for (int i = 0; i < c; ++i) {
        cin >> k3[i];
    }
    sort(k.begin(), k.end());
    sort(k2.begin(), k2.end());
    sort(k3.begin(), k3.end());
    vector<int> rk;
    for (int i = a - x; i < a; ++i) {
        rk.push_back(k[i]);
    }
    for (int i = b - y; i < b; ++i) {
        rk.push_back(k2[i]);
    }
    sort(rk.begin(), rk.end());
    int j = 0;
    for (int i = k3.size() - 1; i >= 0; --i) {
        if (j >= rk.size()) break;
        if (rk[j] >= k3[i]) break;
        rk[j] = k3[i];
        ++j;
    }
    long long ans = 0;
    for (int i = 0; i < rk.size(); ++i) {
        ans += rk[i];
    }
    cout << ans << endl;
    return 0;
}

