#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, s;
    cin >> n >> s;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
    }
    int ans = 0;
    sort(all.begin(), all.end());
    for (int i = 0; i < n; ++i) {
        int u = min(s, all[i].second);
        ans += u * all[i].first;
        s -= u;
    }
    cout << ans << endl;
    return 0;
}
