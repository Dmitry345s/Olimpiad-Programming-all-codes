#include<bits/stdc++.h>

using namespace std;

const long long INF = 5e18;

void divide(int c, vector<vector<long long>> & dp, vector<vector<int>> & opt, vector<vector<long long>> & cnt, int l, int r, int cl, int cr) {
    if (l >= r) return;
    int m = (l + r) / 2;
    //cout << m << " " << cl << " " << cr << endl;
    for (int i = cl; i < min(cr, m); ++i) {
        long long cur = dp[i][c - 1] + cnt[i][m];
        //cout << "! " << cnt[i][m] << endl;
        dp[m][c] = min(dp[m][c], dp[i][c - 1] + cnt[i][m]);
        if (cur == dp[m][c]) {
            opt[m][c] = i;
        }
    }
    //cout << m << " " << c << " " << dp[m][c] << endl;
    divide(c, dp, opt, cnt, l, m, cl, opt[m][c] + 1);
    divide(c, dp, opt, cnt, m + 1, r, opt[m][c], cr);
}

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> ls(n), t(n);
    cin >> t[0];
    for (int i = 1; i < n; ++i) {
        cin >> ls[i] >> t[i];
    }
    vector<long long> pr(n + 1);
    for (int i = 1; i <= n; ++i) {
        pr[i] = pr[i - 1] + t[i - 1];
    }
    vector<long long> pr2(n + 1);
    for (int i = 1; i <= n; ++i) {
        pr2[i] = pr2[i - 1] + ls[i - 1];
    }
    vector<vector<long long>> cnt(n, vector<long long> (n));
    for (int l = 0; l < n; ++l) {
        int c = l;
        long long cur = 0;
        for (int r = l; r < n; ++r) {
            if (c + 1 <= r) {
                cur += (pr[r] - pr[c + 1]) * ls[r];
            }
            //cout << pr2[r + 1] - pr2[c + 2] << " " << pr2[c + 2] - pr2[l + 1] << " " << l << " " << c << " " << r;
            while (c + 1 < r && pr2[r + 1] - pr2[(c + 1) + 1] > pr2[(c + 1) + 1] - pr2[l + 1]) {
                //cout << pr2[r + 1] - pr2[c + 2] << " " << pr2[c + 2] - pr2[l + 1] << " " << l << " " << c << " " << r;
                cur -= (pr2[r + 1] - pr2[(c + 1) + 1]) * t[c + 1];
                cur += (pr2[(c + 1) + 1] - pr2[l + 1]) * t[c + 1];
                c++;
            }
            //cout << c << " " << r << " " << pr[r] - pr[c + 1] << endl;
            cnt[l][r] = cur;
            //cout << l << " " << r << " " << cnt[l][r] << endl;
        }
    }
    vector<vector<long long>> dp(n, vector<long long> (k, INF));
    vector<vector<int>> opt(n, vector<int> (k));
    for (int i = 0; i < n; ++i) {
        dp[i][0] = 0;
        for (int j = 0; j < i; ++j) {
            dp[i][0] += t[j] * (pr2[i + 1] - pr2[j + 1]);
        }
        //cout << dp[i][0] << endl;
    }
    for (int i = 1; i < k; ++i) {
        divide(i, dp, opt, cnt, 0, n, 0, n);
    }
    int last = n - 1;
    long long now = dp[n - 1][k - 1];
    long long cur = 0;
    long long cur2 = 0;
    for (int i = n - 1; i >= 0; --i) {
        //cout << cur << " " << cur2 << endl;
        if (cur + dp[i][k - 1] < now) {
            now = cur + dp[i][k - 1];
            last = i;
        }
        cur2 += t[i];
        cur += cur2 * ls[i];
    }
    cout << now << endl;
    vector<int> ans;
    for (int i = k - 1; i >= 0; --i) {
        ans.push_back(last);
        last = opt[last][i];
    }
    reverse(ans.begin(), ans.end());
    for (int i = 0; i < k; ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
