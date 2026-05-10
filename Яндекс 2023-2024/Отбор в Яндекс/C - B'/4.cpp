#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n), rev(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
        rev[a[i]] = i;
    }
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        --b[i];
    }
    int minm = n, ans = 0;
    for (int i = n - 1; i >= 0; --i) {
        if (minm < rev[b[i]]) {
            ans += 1;
        }
        minm = min(minm, rev[b[i]]);
    }
    cout << ans << endl;
    return 0;
}
