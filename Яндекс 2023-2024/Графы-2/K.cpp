#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].first >> a[i].second;
    }
    int s, t;
    cin >> s >> t;
    --s; --t;
    vector<long long> d(n, 2e15), used(n, 0);
    d[s] = 0;
    used[s] = 1;
    int last = s;
    for (int _ = 0; _ < n - 1; ++_) {
        long long now = 2e15, nlast = -1;
        for (int j = 0; j < n; ++j) {
            if (used[j]) continue;
            long long dif = 1ll * (a[last].first - a[j].first) * (a[last].first - a[j].first) +
            1ll * (a[last].second - a[j].second) * (a[last].second - a[j].second);
            if (d[last] + dif < d[j]) {
                d[j] = d[last] + dif;
            }
            if (d[j] < now) {
                nlast = j;
                now = d[j];
            }
        }
        last = nlast;
        used[last] = 1;
    }
    cout << d[t] << endl;
    return 0;
}
