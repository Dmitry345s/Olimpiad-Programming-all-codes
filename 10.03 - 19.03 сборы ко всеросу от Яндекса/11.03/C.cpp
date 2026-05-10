#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

signed main() {
    int l, n;
    cin >> l >> n;
    string s;
    cin >> s;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'M') {
            a[i] = 1;
        }
    }
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    /*if (l == 1) {
        int cnt = n;
        vector<int> all;
        for (int i = 0; i < n; ++i) {
            if (a[i] == 0) {
                all.push_back(c[i]);
                cnt--;
            }
        }
        sort(all.begin(), all.end());
        for (int i = 0; i < cnt; ++i) {
            cout << 0 << endl;
        }
        int now = 0;
        for (int i = 0; i < (int)all.size(); ++i) {
            now += all[i];
            cout << now << endl;
        }
        return 0;
    }*/
    vector<vector<int>> dp(n / l + 2, vector<int> (1 << (l - 1)));
    for (int j = 0; j < n / l + 1; ++j) {
        for (int k = 0; k < (1 << (l - 1)); ++k) {
            dp[j][k] = INF;
        }
    }
    vector<vector<int>> st = dp;
    dp[0][0] = 0;
    for (int i = 0; i < n; ++i) {
        vector<vector<int>> rdp = st;
        for (int j = 0; j <= i / l; ++j) {
            for (int k = 0; k < (1 << (l - 1)); ++k) {
                for (int u = 0; u < 2; ++u) {
                    int x = (k << 1) + u;
                    int y = (x & ((1 << (l - 1)) - 1));
                    if (x == (1 << (l - 1))) {
                        rdp[j + 1][y] = min(rdp[j + 1][y], dp[j][k] + (u != a[i]) * c[i]);
                    } else {
                        rdp[j][y] = min(rdp[j][y], dp[j][k] + (u != a[i]) * c[i]);
                    }
                }
            }
        }
        dp = rdp;
    }
    int ans = INF;
    vector<int> rans;
    for (int j = n / l; j >= 1; --j) {
        for (int k = 0; k < (1 << (l - 1)); ++k) {
            ans = min(ans, dp[j][k]);
        }
        rans.push_back(ans);
    }
    reverse(rans.begin(), rans.end());
    for (int i = 0; i < n / l; ++i) {
        cout << rans[i] << endl;
    }
    return 0;
}
