#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 2e4 + 1, INF = 1e18;
int pref1[MAX], pref2[MAX], dte[MAX];

int get(int l, int r) {
    int u = pref2[r + 1] - pref2[l];
    int u2 = pref1[r + 1] - pref1[l];
    return u - u2 * dte[r];
}

void go(int l, int r, int optl, int optr, vector<int> & was, vector<int> & will) {
    if (l > r) return;
    int optm = optl;
    int m = (l + r) / 2;
    for (int i = optl; i <= min(m - 1, optr); ++i) {
        int now = get(i + 1, m) + was[i];
        if (now < will[m]) {
            will[m] = now;
            optm = i;
        }
    }
    go(l, m - 1, optl, optm, was, will);
    go(m + 1, r, optm, optr, was, will);
}

signed main() {
    int n;
    cin >> n;
    vector<int> d(n);
    vector<int> w(n);
    for (int i = 0; i < n; ++i) {
        cin >> w[i] >> d[i];
    }
    w.push_back(0);
    dte[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        dte[i] = dte[i + 1] + d[i];
    }
    for (int i = 0; i < n + 1; ++i) {
        pref1[i + 1] = pref1[i] + w[i];
        pref2[i + 1] = pref2[i] + w[i] * dte[i];
    }
    vector<int> dp(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        dp[i] = get(0, i);
    }
    for (int tt = 2; tt <= 3; ++tt) {
        vector<int> ndp(n + 1, INF);
        go(0, n, 0, n, dp, ndp);
        dp = ndp;
    }
    cout << dp[n] << endl;
    return 0;
}
