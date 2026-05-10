#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    multiset<int> all;
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        all.insert(a);
    }
    for (int i = 0; i < k; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            auto it = all.begin();
            int u = *it;
            if (u < 0) {
                all.erase(it);
                all.insert(-u);
            }
        } else {
            auto it = all.end();
            --it;
            int u = *it;
            if (u > 0) {
                all.erase(it);
                all.insert(-u);
            }
        }
    }
    int ans = 0;
    for (int v : all) {
        ans += v;
    }
    cout << ans << endl;
    return 0;
}

