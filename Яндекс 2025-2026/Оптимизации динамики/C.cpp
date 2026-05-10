#include<bits/stdc++.h>

# define int long long

using namespace std;
using ld = long double;

const int MAX = 1e5 + 1;
const ld INF = 2e18;

long long pref1[MAX], pref2[MAX];

ld tr(int l, int r) {
    long long x = pref1[r + 1] - pref1[l];
    return pref2[r + 1] - pref2[l] - ((ld)x * x) / (r - l + 1);
}

void trdo(int l, int r, int optl, int optr, vector<ld> & was, vector<ld> & will) {
    if (r < l) return;
    int m = (l + r) / 2;
    int optm = -1;
    for (int i = optl; i <= min(m - 1, optr); ++i) {
        ld now = was[i] + tr(i + 1, m);
        if (now < will[m]) {
            will[m] = now;
            optm = i;
        }
    }
    trdo(l, m - 1, optl, optm, was, will);
    trdo(m + 1, r, optm, optr, was, will);
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    sort(x.begin(), x.end());
    for (int i = 0; i < n; ++i) {
        pref2[i + 1] = pref2[i] + 1ll * x[i] * x[i];
        pref1[i + 1] = pref1[i] + x[i];
    }
    vector<ld> dp(n, INF);
    for (int i = 0; i < n; ++i) {
        dp[i] = tr(0, i);
    }
    for (int tt = 2; tt <= k; ++tt) {
        vector<ld> ndp(n, INF);
        trdo(0, n - 1, 0, n - 1, dp, ndp);
        dp = ndp;
    }
    cout << setprecision(30) << dp[n - 1] << endl;
    return 0;
}
