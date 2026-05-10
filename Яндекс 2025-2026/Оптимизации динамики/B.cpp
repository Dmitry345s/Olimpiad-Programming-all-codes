#include<bits/stdc++.h>

# define int long long

using namespace std;

const int INF = 1e18;

vector<string> ans;

void go(int l, int r, string s, vector<vector<int>> & opt) {
    if (l == r) {
        ans.push_back(s);
        return;
    }
    s.push_back('0');
    go(l, opt[l][r], s, opt);
    s.pop_back();
    s.push_back('1');
    go(opt[l][r] + 1, r, s, opt);
    s.pop_back();
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> pref(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }
    vector<vector<int>> dp(n, vector<int> (n, INF));
    vector<vector<int>> opt(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for (int d = 2; d <= n; ++d) {
        for (int l = 0; l < n - d + 1; ++l) {
            int r = l + d - 1;
            int add = pref[r + 1] - pref[l];
            for (int c = opt[l][r - 1]; c <= min(opt[l + 1][r], r - 1); ++c) {
                int now = dp[l][c] + dp[c + 1][r] + add;
                if (now < dp[l][r]) {
                    opt[l][r] = c;
                    dp[l][r] = now;
                }
            }
        }
    }
    go(0, n - 1, "", opt);
    for (auto v : ans) {
        cout << v << endl;
    }
    return 0;
}
