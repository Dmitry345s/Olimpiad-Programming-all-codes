#include<bits/stdc++.h>

using namespace std;

const int INF = 1e9;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> cntt(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        a[i]--;
        cntt[a[i]]++;
    }
    vector<pair<int, int>> all;
    for (int i = 0; i < n; ++i) {
        if (!all.empty() && all.back().first == a[i]) {
            all.back().second++;
        } else {
            all.push_back({a[i], 1});
        }
    }
    for (int k = 0; k < m; ++k) {
        int rans = INF;
        int maxm1 = 0, maxm = -1;
        for (int j = 0; j < m; ++j) {
            if (j == k) continue;
            if (maxm1 < cntt[j]) {
                maxm1 = cntt[j];
                maxm = j;
            }
        }
        vector<int> cnt1(n + 1);
            vector<int> cnt2(n + 1);
            for (int i = n - 1; i >= 0; --i) {
                cnt1[i] = cnt1[i + 1] + (a[i] == maxm);
                cnt2[i] = cnt2[i + 1] + (a[i] == k);
            }
            vector<int> dp(n, INF);
            if (a[0] != maxm && a[0] != k) {
                dp[0] = 1;
            } else {
                dp[0] = 0;
            }
            dp[1] = 2 - max((a[0] == k) + (a[1] == k), (a[0] == maxm) + (a[1] == maxm));
            for (int i = 2; i < n; ++i) {
                dp[i] = min(dp[i], dp[i - 2] + 2 - max((a[i - 1] == k) + (a[i] == k), (a[i - 1] == maxm) + (a[i] == maxm)));
            }
            int ans = INF;
            for (int i = 0; i < n; ++i) {
                ans = min(ans, dp[i] + n - 1 - i - max(cnt1[i + 1], cnt2[i + 1]));
            }
            rans = min(rans, ans);
    cout << rans << endl;
    }
    return 0;
}
/*int now = 0;
array<int, 2> cnt;
for (int j = 0; j < (int)all.size(); ++j) {
    if (all[j].first == i && j != 0 && j != (int)all.size() - 1) {
        cnt[now % 2]++;
        now += all[j].second;
        cnt[now % 2]++;
    } else {
        now += all[j].second;
    }
}
int maxm = 0;
for (int j = 0; j < m; ++j) {
    if (j == i) continue;
    maxm = max(maxm, cntt[j]);
}
cout << n - cntt[i] - maxm << endl;
int ans = n - cntt[i] - maxm + min(cnt[0], cnt[1]);
cout << ans << endl;*/
