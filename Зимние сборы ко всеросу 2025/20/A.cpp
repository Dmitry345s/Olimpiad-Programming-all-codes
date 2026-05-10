#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(m);
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> a[i].first >> b[i];
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    vector<int> pref(m + 1);
    pref[0] = 0;
    for (int i = 0; i < m; ++i) {
        pref[i + 1] = pref[i] + a[i].first;
    }
    int ans = 0;
    for (int i = 0; i < m; ++i) {
        int now = a[i].first;
        int nt = n - 1;
        int x = b[a[i].second];
        int j = lower_bound(a.begin(), a.end(), pair<int, int>{x, -1}) - a.begin();
        if (j <= i) {
            nt++;
            now = 0;
        }
        if (m - j > nt) {
            now += pref[m] - pref[m - n];
        } else {
            now += pref[m] - pref[j];
            now += (nt - m + j) * x;
        }
        //cout << i << " " << now << " " << x << endl;
        ans = max(ans, now);
    }
    cout << ans << endl;
    return 0;
}
