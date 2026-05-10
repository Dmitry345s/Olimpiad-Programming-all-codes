#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i];
    }
    vector<int> bgo(n + 1, n + 1);
    map<int, int> mp;
    mp[pref[n]] = n;
    for (int i = n - 1; i >= 0; --i) {
        int u = n + 1;
        if (mp.find(pref[i]) != mp.end()) {
            u = mp[pref[i]];
        }
        bgo[i] = min(bgo[i + 1], u);
        mp[pref[i]] = min(u, i);
    }
    vector<vector<int>> bups(n + 2, vector<int> (20));
    vector<vector<int>> cnt(n + 2, vector<int> (20));
    for (int i = 0; i < 20; ++i) {
        bups[n + 1][i] = n + 1;
        cnt[n + 1][i] = 0;
    }
    for (int i = n; i >= 0; --i) {
        bups[i][0] = bgo[i];
        if (bgo[i] != n + 1) {
            cnt[i][0] = 1;
        }
        for (int j = 1; j < 20; ++j) {
            bups[i][j] = bups[bups[i][j - 1]][j - 1];
            cnt[i][j] = cnt[i][j - 1] + cnt[bups[i][j - 1]][j - 1];
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        --l;
        int ans = 0;
        for (int j = 19; j >= 0; --j) {
            if (bups[l][j] <= r) {
                ans += cnt[l][j];
                l = bups[l][j];
            }
        }
        cout << ans << endl;
    }
    return 0;
}
