#include<bits/stdc++.h>
#pragma GCC optimize("O3")

using namespace std;

mt19937 rnd(time(0));

long long mod = 1e9 + 7;
long long p = 207997;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<long long> ps(n + 1);
    ps[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        ps[i] = (ps[i - 1] * p);
    }
    vector<long long> h(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        h[a] = (h[a] + ps[b]);
        h[b] = (h[b] + ps[a]);
    }
    unordered_map<long long, int> mp;
    long long ans = 0;
    for (int i = 1; i <= n; ++i) {
        ans += mp[h[i]];
        mp[h[i]]++;
        h[i] = (h[i] + ps[i]);
        ans += mp[h[i]];
        mp[h[i]]++;
    }
    cout << ans << endl;
    return 0;
}
