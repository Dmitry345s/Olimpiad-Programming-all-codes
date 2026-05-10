#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> b[i] >> c[i];
    }
    vector<int> dp((1 << n) - 1, 1e9), p((1 << n) - 1, -1), cnt((1 << n) - 1, 0);
    dp[0] = k;
    cnt[0] = 0;
    int ans = 0, now = 0;
    for (int i = 0; i < (1 << n); ++i) {
        for (int j = 0; j < n; ++j) {
            if ((i >> j) & 1) continue;
            if (a[j] <= dp[i] && dp[i] <= b[j]) {
                dp[i + (1 << j)] = dp[i] + c[j];
                cnt[i + (1 << j)] = cnt[i] + 1;
                if (cnt[i + (1 << j)] > ans) {
                    ans = cnt[i + (1 << j)];
                    now = i + (1 << j);
                }
                p[i + (1 << j)] = j;
            }
        }
    }
    cout << cnt[now] << endl;
    vector<int> rans;
    while(p[now] != -1) {
        rans.push_back(p[now]);
        now -= (1 << p[now]);
    }
    reverse(rans.begin(), rans.end());
    for (int i = 0; i < (int)rans.size(); ++i) {
        cout << rans[i] + 1 << " ";
    }
    return 0;
}
