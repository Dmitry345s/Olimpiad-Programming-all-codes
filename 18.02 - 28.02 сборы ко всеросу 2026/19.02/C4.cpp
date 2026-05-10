#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> p(n), s(n);
    for (int i = 0; i < n; ++i) cin >> p[i];
    for (int i = 0; i < n; ++i) cin >> s[i];
    int ans = 1;
    for (int i = 1; i <= n; ++i) {
        ans = (ans * i) % MOD;
    }
    cout << ans << endl;
    return 0;
}
