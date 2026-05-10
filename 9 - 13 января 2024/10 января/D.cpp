#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int w, h;
    cin >> w >> h;
    int n;
    cin >> n;
    vector<pair<int, int>> a(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    a.back().first = a[0].first;
    a.back().second = a[n - 1].second;
    int ans = 0;
    for (int i = 0; i < n + 1; ++i) {
        int i2 = (i + 1) % (n + 1);
        ans += (a[i].first - a[i2].first) * (a[i].second + a[i2].second);
        //cout << ans << endl;
    }
    ans = abs(ans);
    //cout << ans << endl;
    long double ans2 = (long double)ans / 2;
    ans2 = abs((a[0].first - a[n - 1].first) * (a[0].second - a[n - 1].second)) - ans2;
    cout << setprecision(20) << abs(ans2) << endl;
}
