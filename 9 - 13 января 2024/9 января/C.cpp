#include<bits/stdc++.h>

#define int long long

using namespace std;

int gcd(int a, int b) {
    if (a == 0) {
        return b;
    }
    return gcd(b % a, a);
}

vector<int> st, st2(1e4 + 2), st3(1e4 + 2);

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    int cnt = 0, cnt2 = 0;
    int flag = 1;
    if (m > k) {
        flag = 0;
    }
    for (int i = 1; i <= max(k, m); ++i) {
        if (m % i == 0) {
            if (i <= m) {
                st3[i] = st.size();
                st.push_back(i);
            }
        }
        if (i > k) continue;
        if (gcd(i, m) != 1 || i == 1) {
            //cout << i << " " << i % m << endl;
            if (i % m != 0) {
                st2[gcd(i, m)] += 1;
                cnt++;
            } else {
                cnt2 += 1;
            }
        }
    }
    //cout << cnt2 << endl;
    int mod = 1e9 + 7;
    //cout << 0 << endl;
    vector<vector<int>> dp(n, vector<int> (st.size()));
    //cout << cnt2 << endl;
    for (int i = 1; i <= k; ++i) {
        int u = lower_bound(st.begin(), st.end(), m / gcd(m, i)) - st.begin();
        dp[0][u] += 1;
    }
    //cout << dp[0][1] << endl;
    for (int i = 0; i < n - 1; ++i) {
        //cout << dp[i][0] << endl;
        for (int j = 0; j < st.size(); ++j) {
            for (int l = 0; l < st.size(); ++l) {
                int u = st3[st[j] / gcd(st[j], st[l])];
                dp[i + 1][u] += (dp[i][j] * st2[st[l]]) % mod;
                dp[i + 1][u] %= mod;
            }
            dp[i + 1][0] += (dp[i][j] * cnt2) % mod;
            dp[i + 1][0] %= mod;
            dp[i + 1][j] += (dp[i][j] * (k - cnt2 - cnt)) % mod;
            dp[i + 1][j] %= mod;
        }
    }
    //cout << dp[1][1] << endl;
    cout << dp.back()[0] << endl;
}
