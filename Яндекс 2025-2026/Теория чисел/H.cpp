#include<bits/stdc++.h>

# define int long long

using namespace std;

const int MAX = 5e4 + 1, INF = 1e12 + 1;
int a[MAX];
int ans = 0;

void solve(int l, int r) {
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    solve(l, m);
    solve(m, r);
    vector<array<int, 3>> suf(m - l + 1);
    vector<int> gds(m - l + 1);
    suf.back() = {-INF, 0, 0};
    for (int i = m - 1; i >= l; --i) {
        suf[i - l][0] = max(suf[i - l + 1][0], a[i]);
        suf[i - l][1] = suf[i - l + 1][1] + a[i];
        suf[i - l][2] = __gcd(suf[i - l + 1][2], abs(a[i]));
    }
    for (int i = m - 1; i >= l; --i) {
        if (i == l || suf[i - l - 1][2] != suf[i - l][2]) {
            gds[i - l] = 1;
        }
    }
    vector<array<int, 3>> pref(r - m + 1);
    vector<int> gdp(r - m + 1);
    pref[0] = {-INF, 0, 0};
    for (int i = m; i < r; ++i) {
        pref[i - m + 1][0] = max(pref[i - m][0], a[i]);
        pref[i - m + 1][1] = pref[i - m][1] + a[i];
        pref[i - m + 1][2] = __gcd(pref[i - m][2], abs(a[i]));
    }
    for (int i = m; i < r; ++i) {
        if (i == r - 1 || pref[i - m + 1][2] != pref[i - m + 2][2]) {
            gdp[i - m + 1] = 1;
        }
    }
    vector<int> now;
    int u = m;
    int nowmx = -INF;
    int in = -1;
    for (int i = m - 1; i >= l; --i) {
        while (u < r && pref[u - m + 1][0] <= suf[i - l][0]) {
            if (pref[u - m + 1][1] > nowmx) {
                in = u;
                nowmx = pref[u - m + 1][1];
            }
            if (gdp[u - m + 1]) {
                now.push_back(in - m + 1);
                nowmx = -INF;
                in = -1;
            }
            ++u;
        }
        for (auto tt : now) {
            ans = max(ans, __gcd(suf[i - l][2], pref[tt][2]) * (pref[tt][1] + suf[i - l][1] - suf[i - l][0]));
        }
        if (in != -1 && in != m) {
            ans = max(ans, __gcd(suf[i - l][2], pref[in - m][2]) * (pref[in - m][1] + suf[i - l][1] - suf[i - l][0]));
        }
    }
    now.clear();
    u = m - 1;
    nowmx = -INF;
    in = -1;
    for (int i = m; i < r; ++i) {
        while (u >= l && suf[u - l][0] < pref[i - m + 1][0]) {
            if (suf[u - l][1] > nowmx) {
                nowmx = suf[u - l][1];
                in = u;
            }
            if (gds[u - l]) {
                now.push_back(in - l);
                in = -1;
                nowmx = -INF;
            }
            u--;
        }
        for (auto tt : now) {
            ans = max(ans, __gcd(suf[tt][2], pref[i - m + 1][2]) * (pref[i - m + 1][1] + suf[tt][1] - pref[i - m + 1][0]));
        }
        if (in != -1 && in != m - 1) {
            ans = max(ans, __gcd(suf[in - l + 1][2], pref[i - m + 1][2]) * (pref[i - m + 1][1] + suf[in - l + 1][1] - pref[i - m + 1][0]));
        }
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    solve(0, n);
    cout << ans << endl;
}
