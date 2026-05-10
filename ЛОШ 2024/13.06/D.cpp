#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    sort(c.begin(), c.end());
    int q;
    cin >> q;
    vector<int> qs(q);
    for (int i = 0; i < q; ++i) {
        cin >> qs[i];
    }
    if (k == 2) {
        unordered_map<int, int> mp;
        for (int i = 0; i < n; ++i) {
            mp[c[i]]++;
        }
        for (int i = 0; i < q; ++i) {
            int ans = 0;
            for (int j = 0; j < n; ++j) {
                ans += mp[qs[i] - c[j]];
            }
            cout << ans % 2999 << endl;
        }
        return 0;
    }
    vector<int> now(c.back() * k + 1);
    vector<int> sec(c.back() * k + 1);
    vector<int> fu(c.back() * k + 1);
    now[0] = 1;
    int mod = 2999;
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int u = 0; u < (int)now.size(); ++u) {
                if (u + c[j] < (int)sec.size()) {
                    sec[u + c[j]] += now[u];
                    sec[u + c[j]] %= mod;
                }
            }
        }
        now = sec;
        sec = fu;
    }
    for (int i = 0; i < q; ++i) {
        if (qs[i] > c.back() * k) {
            cout << 0 << endl;
        } else {
            cout << now[qs[i]] << endl;
        }
    }
    return 0;
}
