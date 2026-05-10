#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

//#define int long long

using namespace std;
using ll = long long;

const int MOD = 1e9 + 7;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    vector<int> c;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        c.push_back(a[i]);
    }
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
        c.push_back(b[i]);
    }
    //c.push_back(0);
    sort(c.begin(), c.end());
    c.erase(unique(c.begin(), c.end()), c.end());
    for (int i = 0; i < n; ++i) {
        a[i] = lower_bound(c.begin(), c.end(), a[i]) - c.begin();
        b[i] = lower_bound(c.begin(), c.end(), b[i]) - c.begin();
    }
    vector<pair<int, int>> dp[n + 1];
    int ws[(int)c.size()];
    int now[(int)c.size()];
    fill(ws, ws + (int)c.size(), 0);
    fill(now, now + (int)c.size(), 0);
    ws[0] = 1;
    dp[0].push_back({0, 1});
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < (int)c.size(); ++j) {
            now[max(j, a[i - 1])] += ws[j];
            if (now[max(j, a[i - 1])] >= MOD) now[max(j, a[i - 1])] -= MOD;
            now[max(j, b[i - 1])] += ws[j];
            if (now[max(j, b[i - 1])] >= MOD) now[max(j, b[i - 1])] -= MOD;
        }
        int cnt = 0;
        for (int j = 0; j < (int)c.size(); ++j) {
            if (now[j] != 0) {
                cnt++;
            }
            ws[j] = now[j];
        }
        dp[i].resize(cnt);
        int y = 0;
        for (int j = 0; j < (int)c.size(); ++j) {
            if (now[j]) {
                dp[i][y] = {j, now[j]};
                y++;
                now[j] = 0;
            }
        }
    }
    int ls[(int)c.size()];
    for (int i = 0; i < (int)c.size(); ++i) {
        ls[i] = 0;
    }
    ls[0] = 1;
    long long ans = 0;
    int ndp[(int)c.size()];
    fill(ndp, ndp + (int)c.size(), 0);
    for (int i = n - 1; i >= 0; --i) {
        int nls[(int)c.size()];
        for (int j = 0; j < (int)c.size(); ++j) {
            nls[j] = 0;
        }
        for (int j = 0; j < (int)c.size(); ++j) {
            nls[max(j, a[i])] += ls[j];
            if (nls[max(j, a[i])] >= MOD) nls[max(j, a[i])] -= MOD;
            nls[max(j, b[i])] += ls[j];
            if (nls[max(j, b[i])] >= MOD) nls[max(j, b[i])] -= MOD;
        }
        //for (int j = 0; j < (int)c.size(); ++j) ls[j] = nls[j];
        for (auto [in, cnt] : dp[i]) {
            ndp[in] = cnt;
        }
        int sum0 = 0;
        int sum1 = 0;
        for (int j = (int)c.size() - 1; j >= 0; --j) {
            sum0 += ls[j];
            if (sum0 >= MOD) sum0 -= MOD;
            int dif0 = c[j] - c[b[i]];
            int dif1 = c[j] - c[a[i]];
            int dif2 = sum0;
            int dif3 = sum1;
            if (dif0 > 0) {
                ans = (ans + 1ll * dif0 * ((1ll * ndp[j] * dif2) % MOD)) % MOD;
                ans = (ans + 1ll * dif0 * ((1ll * ls[j] * dif3) % MOD)) % MOD;
            }
            if (dif1 > 0) {
                ans = (ans + 1ll * dif1 * ((1ll * ndp[j] * dif2) % MOD)) % MOD;
                ans = (ans + 1ll * dif1 * ((1ll * ls[j] * dif3) % MOD)) % MOD;
            }
            sum1 += ndp[j];
            if (sum1 >= MOD) sum1 -= MOD;
        }
        for (int j = 0; j < (int)c.size(); ++j) {
            ls[j] = nls[j];
            ndp[j] = 0;
        }
    }
    cout << ans << endl;
    return 0;
}
