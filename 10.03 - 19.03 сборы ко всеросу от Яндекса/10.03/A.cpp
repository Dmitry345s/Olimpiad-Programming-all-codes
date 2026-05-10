#include<bits/stdc++.h>

#define int long long

using namespace std;

int f(int r) {
    int ans = 1 + 4 * r + 4 * (int)((long double)r / sqrt(2));
    return ans;
}

const int INF = 2e9;
const int C = 3e5;

signed main() {
    int n;
    cin >> n;
    vector<int> r(n);
    vector<int> c(n);
    int sum = 0;
    vector<int> cnt(C);
    for (int u = 0; u < C; ++u) {
        cnt[u] = f(u);
        //cout << cnt[u] << endl;
    }
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
        r[i] = r[i] % C;
    }
    for (int i = 0; i < n; ++i) {
        c[i] = cnt[r[i]];
        //cout << c[i] << endl;
        sum += c[i];
    }
    sum %= 8;
    vector<int> dp(8, n + 1);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        vector<int> ndp(8, n + 1);
        int u = c[i] % 8;
        for (int j = 0; j < 8; ++j) {
            ndp[(u + j) % 8] = min(ndp[(u + j) % 8], dp[j] + 1);
            ndp[j] = min(ndp[j], dp[j]);
        }
        dp = ndp;
    }
    cout << dp[sum] << endl;
    return 0;
}
