#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7;

set<vector<int>> st;

void rstup(int n, vector<int> a, vector<int> now = {}) {
    if (now.size() == n) {
        vector<int> to_add(n);
        for (int i = 0; i < n; ++i) {
            int j = i;
            while (j >= 0 && now[j] <= now[i]) {
                --j;
            }
            to_add[i] = j;
        }
        st.insert(to_add);
        return;
    }
    for (int i = 1; i <= a[(int)now.size()]; ++i) {
        now.push_back(i);
        rstup(n, a, now);
        now.pop_back();
    }
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i] = min(a[i], n);
        //a[i] -= 1;
    }
    /*vector<vector<int>> dp(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = i; j < n; ++j) {
            dp[i][j] = 1;
        }
    }
    vector<vector<int>> ch(n, vector<int> (n));
    for (int l = 0; l < n; ++l) {
        ch[l][l] = (a[l] == 1);
        for (int r = l + 1; r < n; ++r) {
            if (a[r] == 1) {
                ch[l][r] = 1;
            }
            ch[l][r] |= ch[l][r - 1];
        }
    }
    for (int x = 2; x < n + 1; ++x) {
        vector<vector<int>> new_dp = dp;
        for (int d = 2; d <= n; ++d) {
            for (int l = 0; l < n; ++l) {
                int r = (l + d - 1);
                if (r >= n) continue;
                for (int c = l + 1; c < r; ++c) {
                    if (a[c] >= x) {
                        new_dp[l][r] = (new_dp[l][r] + (new_dp[l][c - 1] * dp[c + 1][r]) * (ch[c + 1][r] || (x == 2)) % MOD + (new_dp[l][c - 1] * dp[c + 1][r - 1] * (ch[c + 1][r - 1] || (x == 2)) * (a[r] >= x))) % MOD;
                    }
                }
                if (a[l] >= x) {
                    new_dp[l][r] = (new_dp[l][r] + dp[l + 1][r] * (ch[l + 1][r] || (x == 2)) + dp[l + 1][r - 1] * (ch[l + 1][r - 1] || (x == 2)) * (a[r] >= x)) % MOD;
                }
                if (a[r] >= x) {
                    //new_dp[l][r] = (new_dp[l][r] + dp[l][r - 1]) % MOD;
                }
            }
        }
        dp = new_dp;
        for (int l = 0; l < n; ++l) {
            for(int r = l; r < n; ++r) {
                cout << x << " " << l << " " << r << " " << dp[l][r] << endl;
            }
        }
    }
    cout << dp[0][n - 1] << endl;*/
    /*vector<vector<vector<int>>> dp(n, vector<vector<int>> (n, vector<int> (n + 1))), dp2 = dp;
    dp[0][0][0] = 1;
    for (int i = 0; i <= a[0]; ++i) {
        dp2[0][0][i] = 1;
    }
    for (int r = 1; r < n; ++r) {
        for (int last = 0; last <= a[r]; ++last) {
            int lastupd = r;
            int now = 0;
            dp[r][r][last] = (last == 0);
            dp2[r][r][last] = 1;
            for (int to = r - 1; to >= 0; --to) {
                if (a[to] < last) continue;
                if (a[to] >= last) {
                    int to_get = sum(dp[to + 1][r - 1]) - sum(dp[to + 1][lastupd], last) * now;
                    to_get = max(to_get, 1);
                    for (int l = 0; l <= to; ++l) {
                        dp2[l][r][last] += dp2[l][to][last] * to_get;
                        dp2[l][r][last] += (dp2[l][to][last + 1] + sum(dp[l][to], last + 2)) * to_get;
                        dp[l][r][last] += dp2[l][to][last] * to_get;
                    }
                    now = to_get;
                    lastupd = to;
                }
            }
            dp2[0][r][last] += max((sum(dp[0][r - 1]) - sum(dp[0][lastupd], last) * now), 1);
            dp[0][r][last] += max((sum(dp[0][r - 1]) - sum(dp[0][lastupd], last) * now), 1);
            for (int l = 0; l <= r; ++l) {
                //cout << l << " " << r << " " << last << " " << dp[l][r][last] << " " << dp2[l][r][last] << endl;
            }
        }
    }
    cout << sum(dp[0][n - 1]) << endl;*/
    vector<vector<vector<int>>> dp(n + 1, vector<vector<int>> (n, vector<int> (n)));
    vector<vector<int>> cnt(n, vector<int> (n));
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            dp[1][l][r] = 1;
            cnt[l][r] = 1;
        }
    }
    for (int x = 2; x <= n; ++x) {
        for (int l = 0; l < n; ++l) {
            for (int r = l + x - 1; r < n; ++r) {
                int now = 0;
                for (int c = r - 1; c > l; --c) {
                    if (a[c] >= x) {
                        dp[x][l][r] = (dp[x][l][r] + (cnt[l][c - 1] * dp[x - 1][c + 1][r]) % MOD) % MOD;
                        dp[x][l][r] = (dp[x][l][r] + (dp[x][l][c - 1] * (cnt[c + 1][r] - dp[x - 1][c + 1][r] + MOD) % MOD) % MOD);
                    }
                }
                if (a[l] >= x) {
                    dp[x][l][r] = (dp[x][l][r] + dp[x - 1][l + 1][r]) % MOD;
                    //dp[x][l][r] += (cnt[l + 1][r] - dp[x - 1][l + 1][r]);
                }
                if (a[r] >= x) {
                    dp[x][l][r] = (dp[x][l][r] + dp[x][l][r - 1]) % MOD;
                }
                cnt[l][r] = (cnt[l][r] + dp[x][l][r]) % MOD;
                //cout << x << " " << l << " " << r << " " << dp[x][l][r] << " " << cnt[l][r] << endl;
            }
        }
    }
    cout << cnt[0][n - 1] << endl;
    return 0;
}
