#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 5e4 + 5, INF = 2e6;
int a[MAX];

int solve(int l, int r) {
    if (l + 1 == r) {
        return 0;
    }
    int m = (l + r) / 2;
    int nans = max(solve(m, r), solve(l, m));
    vector<array<int, 3>> pref;
    int mx = -INF, gcd = 0, sum = 0;
    for (int i = m - 1; i >= l; --i) {
        sum += a[i];
        gcd = __gcd(gcd, abs(a[i]));
        mx = max(mx, a[i]);
        pref.push_back({mx, sum, gcd});
    }
    vector<array<int, 3>> pref2;
    mx = -INF, gcd = 0, sum = 0;
    for (int i = m; i < r; ++i) {
        sum += a[i];
        gcd = __gcd(gcd, abs(a[i]));
        mx = max(mx, a[i]);
        pref2.push_back({mx, sum, gcd});
    }
    int now = 0;
    vector<pair<int, int>> to_upd;
    for (int i = 0; i < (int)pref.size(); ++i) {
        while (now < (int)pref2.size() && pref2[now][0] <= pref[i][0]) {
            if ((int)to_upd.size() == 0 || to_upd.back().first != pref2[now][2]) {
                to_upd.push_back({pref2[now][2], pref2[now][1]});
            }
            to_upd.back().second = max(to_upd.back().second, pref2[now][1]);
            now++;
        }
        for (auto [g, s] : to_upd) {
            nans = max(nans, __gcd(g, pref[i][2]) * (pref[i][1] - pref[i][0] + s));
        }
    }
    now = 0;
    to_upd.clear();
    for (int i = 0; i < (int)pref2.size(); ++i) {
        while (now < (int)pref.size() && pref[now][0] <= pref2[i][0]) {
            if ((int)to_upd.size() == 0 || to_upd.back().first != pref[now][2]) {
                to_upd.push_back({pref[now][2], pref[now][1]});
            }
            to_upd.back().second = max(to_upd.back().second, pref[now][1]);
            now++;
        }
        for (auto [g, s] : to_upd) {
            nans = max(nans, __gcd(g, pref2[i][2]) * (pref2[i][1] - pref2[i][0] + s));
        }
    }
    return nans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    cout << solve(0, n) << endl;
    return 0;
}
