#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> cnt(k);
    int ch = 0;
    for (int i = 0; i < k; ++i) {
        cin >> cnt[i];
    }
    int rcnt = 0;
    cnt.insert(cnt.begin(), 0);
    for (int i = 0; i < k; ++i) {
        if (cnt[i + 1] - cnt[i] - 1 <= 2) {
            continue;
        } else {
            rcnt += cnt[i + 1] - cnt[i] - 1 - ((cnt[i + 1] - cnt[i]) % 2) - 1;
        }
    }
    rcnt += n - cnt.back();
    //cout << cnt[0] << endl;
    for (int i = 0; i < k; ++i) {
        if (cnt[i + 1] - cnt[i] - 1 <= 2) continue;
        int u = cnt[i + 1] - cnt[i] - 1 - ((cnt[i + 1] - cnt[i]) % 2) - 1;
        //cout << u << endl;
        for (int j = i + 1; j <= k; ++j) {
            cnt[j] -= u;
        }
    }
    //cout << cnt.back() << endl;
    assert(cnt.back() + 1 < 1e5);
    cnt.erase(cnt.begin());
    vector<int> tr(cnt.back() + 1 + (rcnt % 2));
    for (int i = 0; i < k; ++i) {
        tr[cnt[i]] = 1;
    }
    ////cout << endl;
    ////cout << rcnt << endl;
    //cout << 0 << endl;
    vector<vector<int>> dp(2, vector<int> (k + 1, -(int)1e9));
    dp[0][0] = 0;
    dp[1][1] = tr[1];
    dp[1][0] = 0;
    //cout << tr.size() << endl;
    for (int i = 2; i < (int)tr.size(); ++i) {
        vector<int> ndp(k + 1, -(int)1e9);
        ndp[0] = 0;
        ////cout << i << " ";
        for (int j = 1; j <= k; ++j) {
                ////cout << j << endl;
            ndp[j] = max(ndp[j], dp[1][j]);
            ndp[j] = max(ndp[j], dp[0][j - 1] + tr[i]);
            ////cout << i << " " << j << " " << dp[i][j] << endl;
        }
        dp[0] = dp[1];
        dp[1] = ndp;
    }
    ////cout << endl;
    int ans = 0;
    for (int i = max(0, k - rcnt / 2); i <= k; ++i) {
        ans = max(ans, dp.back()[i]);
    }
    cout << k - ans << endl;
    return 0;
}
