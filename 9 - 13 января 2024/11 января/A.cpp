#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, b;
    cin >> n >> b;
    vector<pair<int, int>> a(n);
    map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    int ans = 0, in1 = -1, in2 = -1;
    for (int i = 0; i < n; ++i) {
        int u = (upper_bound(a.begin(), a.end(), pair<int, int>{b / a[i].first, 1e9}) - a.begin()) - 1;
        if (u < 0 || u <= i) continue;
        if (ans < a[u].first * a[i].first) {
            ans = a[u].first * a[i].first;
            in1 = a[i].second;
            in2 = a[u].second;
        }
    }
    if (ans == 0) {
        cout << 0 << endl;
        return 0;
    }
    cout << ans << endl;
    cout << in1 + 1 << " " << in2 + 1 << endl;
    return 0;
}
