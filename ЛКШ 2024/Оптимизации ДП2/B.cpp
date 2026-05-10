#include<bits/stdc++.h>

using namespace std;

pair<long long, int> ch(long long m, const vector<int> & a, int l) {
    int n = (int)a.size();
    vector<pair<long long, int>> dp(l + n);
    for (int i = 0; i < l; ++i) {
        dp[i] = {0, 0};
    }
    for (int i = l; i < n + l; ++i) {
        dp[i] = dp[i - 1];
        dp[i].first += a[i - l];
        if (l <= i) {
            dp[i] = min(dp[i], pair<long long, int>{dp[i - l].first + m, dp[i - l].second + 1});
            //cout << dp[i - l].first << endl;
        }
        if (m == 1) {
            //cout << dp[i].first << " " << dp[i].second << endl;
        }
        //cout << dp[i].first << " " << dp[i].second << endl;
    }
    return dp.back();
}

long long bin_search(const vector<int> & a, int k, int ls) {
    long long l = -1, r = 1e9 + 69;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (ch(m, a, ls).second > k) {
            l = m;
        } else {
            r = m;
        }
    }
    return ch(r, a, ls).first - 1ll * r * k;
}

signed main() {
    int n, k, ls;
    cin >> n >> k >> ls;
    string s;
    cin >> s;
    vector<int> a(n, 0), b(n, 1);
    for (int i = 0; i < n; ++i) {
        if ('A' <= s[i] && s[i] <= 'Z') {
            a[i] = 1;
            b[i] = 0;
        }
    }
    cout << min(bin_search(a, k, ls), bin_search(b, k, ls)) << endl;
    return 0;
}
