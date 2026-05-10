#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    map<string, int> mp;
    for (int i = 0; i < m; ++i) {
        string x;
        cin >> x;
        mp[x] = i;
    }
    int cnst;
    cin >> cnst;
    vector<int> d(m);
    for (int i = 0; i < m; ++i) {
        cin >> d[i];
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        auto it = mp.find(a[i]);
        if (it != mp.end()) {
            ans += d[(*it).second];
        } else {
            ans += cnst;
        }
    }
    cout << ans << endl;
    return 0;
}
