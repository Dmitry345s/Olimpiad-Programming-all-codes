#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 998244353;

int f(int x, int y) {
    return ((x ^ y) * (x | y) * (x & y)) % MOD;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> deg(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        deg[a]++;
        deg[b]++;
    }
    vector<int> cnt(2 * m + 1);
    for (int i = 0; i < n; ++i) {
        cnt[deg[i]] += 1;
    }
    vector<pair<int, int>> all;
    for (int i = 0; i < 2 * m + 1; ++i) {
        if (cnt[i] != 0) {
            all.push_back({i, cnt[i]});
        }
    }
    int ans = 0;
    for (int i = 0; i < (int)all.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            int x = all[i].first;
            int y = all[j].first;
            ans += all[i].second * all[j].second % MOD * f(x, y) % MOD;
            ans %= MOD;
        }
    }
    cout << ans << endl;
    return 0;
}
