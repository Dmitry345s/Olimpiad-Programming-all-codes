#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7, INF = 2e9;

int fpow(int a, int x) {
    int ans = 1;
    while (x > 0) {
        if (x % 2 == 1) {
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        x /= 2;
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> b(n);
    int maxm = 0;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        maxm = max(maxm, a[i]);
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        maxm = max(maxm, a[i]);
    }
    if (n <= 20) {
        int ans = 0;
        for (int mask = 0; mask < (1 << n); ++mask) {
            vector<int> now(n);
            for (int i = 0; i < n; ++i) {
                if ((mask >> i) & 1) {
                    now[i] = b[i];
                } else {
                    now[i] = a[i];
                }
            }
            vector<int> pref(n + 1, -INF), suf(n + 1, -INF);
            for (int i = 0; i < n; ++i) {
                pref[i + 1] = max(pref[i], now[i]);
            }
            for (int i = n - 1; i >= 0; --i) {
                suf[i] = max(suf[i + 1], now[i]);
            }
            for (int i = 0; i < n; ++i) {
                ans += max(0ll, min(pref[i], suf[i]) - now[i]);
                ans %= MOD;
            }
        }
        cout << ans << endl;
        return 0;
    }
    if (maxm <= 2) {
        int ans = 0;
        for (int i = 2; i < n; ++i) {
            ans = (ans + (fpow(2, n - i - 1) * (n - i)) % MOD * (i - 1)) % MOD;
        }
        cout << ans << endl;
    }
}
/*
    if (n <= 1e4 && m <= 1e4 && q <= 1e4) {
        vector<set<pair<int, int>>> ln(n);
        vector<set<pair<int, int>>> st(m);
        map<pair<int, int>, array<int, 4>> mp;
        map<pair<int, int>, array<int, 4>> mp2;
        for (int i = 0; i < q; ++i) {
            auto [t, x, y] = all[i];
            if (t == 1) {
                ln[x].insert({y, 1});
                st[y].insert({x, 1});
                auto now = ln[x].lower_bound({y, 1});
                auto now2 = st[y].lower_bound({x, 1});
                auto now_ = now;
                now_++;
                auto now2_ = now2;
                now2_++;
                if (now != ln[x].begin()) {
                    auto now__ = now;
                    --now__;
                    if (now_ != ln[x].end()) {
                        if (mp[{x, (*now_).first}][0] == 1) {
                            ans -= mp2[{x, (*now_).first}][0];
                        }
                        mp[{x, (*now_).first}][0] = 0;
                        if (mp[{x, (*now__).first}][2] == 1) {
                            ans -= mp2[{x, (*now__).first}][2];
                        }
                        mp[{x, (*now__).first}][2] = 0;
                    }
                }
                if (now2 != st[y].begin()) {
                    auto now2__ = now2;
                    --now2__;
                    if (now2_ != st[y].end()) {
                        if (mp[{x, (*now2_).first}][1] == 1) {
                            ans -= mp2[{x, (*now2_).first}][1];
                        }
                        mp[{x, (*now2_).first}][1] = 0;
                        if (mp[{x, (*now2__).first}][3] == 1) {
                            ans -= mp2[{x, (*now2__).first}][3];
                        }
                        mp[{x, (*now2__).first}][3] = 0;
                    }
                } else {
                    if (now2_ != st[y].end()) {

                    }
                }
            }
        }
*/
