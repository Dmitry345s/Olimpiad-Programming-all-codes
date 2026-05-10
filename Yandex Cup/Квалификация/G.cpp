#include<bits/stdc++.h>

using namespace std;

const int MAXC = 1e7 + 1;

int cnt = 0;
int lp[MAXC];
int pr[MAXC];
int ch[MAXC];

void sieve() {
    lp[1] = 1;
    ch[1] = 1;
    for (int i = 2; i < MAXC; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr[cnt] = i;
            cnt++;
        }
        for (int j = 0; j < cnt && pr[j] <= lp[i] && pr[j] * i < MAXC; ++j) {
            lp[i * pr[j]] = lp[i];
        }
        int x = i;
        int cnt = 0;
        while (x % lp[i] == 0) {
            x /= lp[i];
            cnt++;
        }
        if (cnt >= 2) {
            ch[i] = ch[x];
        }
        //cout << i << " " << ch[i] << endl;
    }
}

long long solve(int l, int r, vector<int> & a) {
    if (l + 1 == r) {
        return ch[a[l]] * a[l];
    }
    int m = (l + r) / 2;
    long long ans = solve(l, m, a) + solve(m, r, a);
    vector<pair<int, int>> pref;
    vector<pair<int, int>> suf;
    pref.push_back({0, 0});
    suf.push_back({0, 0});
    for (int i = m; i < r; ++i) {
        if (!ch[a[i]]) break;
        int y = __gcd(pref.back().first, a[i]);
        if (y == pref.back().first) {
            pref.back().second++;
        } else {
            pref.push_back({y, 1});
        }
    }
    for (int i = m - 1; i >= l; --i) {
        if (!ch[a[i]]) break;
        int y = __gcd(suf.back().first, a[i]);
        if (y == suf.back().first) {
            suf.back().second++;
        } else {
            suf.push_back({y, 1});
        }
    }
    for (auto [v, cnt] : pref) {
        for (auto [u, cnt2] : suf) {
            ans += 1ll * cnt * cnt2 * __gcd(u, v);
        }
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    sieve();
    while (_--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }
        cout << solve(0, n, a) << endl;
    }
    return 0;
}
