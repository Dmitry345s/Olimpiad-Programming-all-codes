#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 1e5 + 1, INF = 1e18;
int pref1[MAX];
int x[MAX];

int get(int l, int r) {
    return x[r] * (r - l + 1) - (pref1[r + 1] - pref1[l]);
}

void go(int l, int r, int optl, int optr, vector<int> & was, vector<int> & will) {
    if (l > r) return;
    int m = (l + r) / 2;
    int optm = optl;
    for (int i = optl; i <= min(m - 1, optr); ++i) {
        int now = was[i] + get(i + 1, m);
        if (now < will[m]) {
            will[m] = now;
            optm = i;
        }
    }
    go(l, m - 1, optl, optm, was, will);
    go(m + 1, r, optm, optr, was, will);
}

signed main() {
    int n, m, p;
    cin >> n >> m >> p;
    vector<int> d(n - 1);
    vector<int> pref(n);
    for (int i = 0; i < n - 1; ++i) {
        cin >> d[i];
        pref[i + 1] = pref[i] + d[i];
    }
    int fl = 0;
    for (int j = 0; j < m; ++j) {
        int h, t;
        cin >> h >> t;
        --h;
        x[j] = t - pref[h];
        /*if (x[j] < 0) {
            fl += -x[j];
            x[j] = 0;
        }*/
    }
    sort(x, x + m);
    for (int i = 0; i < m; ++i) {
        pref1[i + 1] = pref1[i] + x[i];
    }
    vector<int> dp(m);
    for (int i = 0; i < m; ++i) {
        dp[i] = get(0, i);
    }
    for (int tt = 2; tt <= min(m, p); ++tt) {
        vector<int> ndp(m, INF);
        go(0, m - 1, 0, m - 1, dp, ndp);
        dp = ndp;
    }
    cout << dp[m - 1] + fl << endl;
    return 0;
}
