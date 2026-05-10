#include<bits/stdc++.h>

#define int long long

using namespace std;
using ld = long double;

signed main() {
    int n, k, L;
    cin >> n >> L >> k;
    vector<int> a(n);
    for (int i = 0; i < k; ++i) {
        int b;
        cin >> b;
        --b;
        a[b] = 1;
    }
    vector<pair<ld, ld>> ps(n);
    for (int i = 0; i < n; ++i) {
        cin >> ps[i].first >> ps[i].second;
    }
    vector<ld> dist(n);
    for (int i = 0; i < n; ++i) {
        int j = (i + 1) % n;
        ld x = ps[i].first - ps[j].first;
        ld y = ps[i].second - ps[j].second;
        dist[i] = sqrtl((x * x) + (y * y));
    }
    vector<ld> pref(n + 1);
    vector<ld> pref2(n + 1);
    pref[0] = 0;
    pref2[0] = 0;
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + dist[i];
        if (a[i] == 1) {
            pref2[i + 1] = pref2[i] + dist[i];
        } else {
            pref2[i + 1] = pref2[i];
        }
    }
    ld ans = 0;
    for (int i = 0; i < n; ++i) {
        int l = 0, r = n + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            int rl = i, rr = i + m;
            ld now = 0;
            if (rr < n) {
                now = pref[rr] - pref[rl];
            } else {
                now = pref.back() - (pref[rl] - pref[rr % n]);
            }
            if (now <= L) {
                l = m;
            } else {
                r = m;
            }
        }
        int rl = i;
        int rr = i + l;
        ld now = 0;
        ld now2 = 0;
        if (rr < n) {
            now2 = pref2[rr] - pref2[rl];
            now = pref[rr] - pref[rl];
        } else {
            now2 = pref2.back() - (pref2[rl] - pref2[rr % n]);
            now = pref.back() - (pref[rl] - pref[rr % n]);
        }
        //cout << i << " " << now << endl;
        ld dif = L - now;
        if (a[rr % n] && rr != rl + n) {
            now2 += dif;
        }
        ans = max(now2, ans);
    }
    cout.precision(20);
    cout << fixed;
    cout << pref2.back() - ans << endl;
    return 0;
}
