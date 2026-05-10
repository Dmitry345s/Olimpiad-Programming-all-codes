#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    long double ans = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
        for (int j = 0; j < i; ++j) {
            int x = a[i].first - a[j].first, y = a[i].second - a[j].second;
            ans = max(ans, sqrtl(x * x + y * y));
        }
    }
    cout << setprecision(20) << ans << endl;
    return 0;
}
