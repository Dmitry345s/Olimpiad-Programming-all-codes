#include<bits/stdc++.h>

#define int long long

using namespace std;

int ans = 0;

void algo(vector<int> a, int k, int n, int ch = 1) {
    int MAX = 1e6 + 3;
    vector<vector<int>> cnt(MAX), cnt2(MAX);
    for (int i = 0; i < n; i += 2) {
        cnt[a[i]].push_back(i);
    }
    for (int i = 1; i < n; i += 2) {
        cnt2[a[i]].push_back(i);
    }
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < cnt[i].size(); ++j) {
            int u = cnt[i][j];
            if (n % 2 == 0 && u >= n / 2) break;
            if (n % 2 == 1 && u - ch >= n / 2) break;
            int d1 = k - 2 * u;
            int cor1 = max(u + d1 - 1, u + 1);
            int cor2 = min(u + k - 1, n - u - ch - 1);
            int p1 = lower_bound(cnt[i].begin(), cnt[i].end(), cor1) - cnt[i].begin();
            int p2 = upper_bound(cnt[i].begin(), cnt[i].end(), cor2) - cnt[i].begin();
            ans += max(0ll, p2 - p1);
        }
        //cout << i << " " << ans << endl;
    }
    for (int i = 0; i < MAX; ++i) {
        for (int j = 0; j < cnt2[i].size(); ++j) {
            int u = cnt2[i][j];
            if (n % 2 == 0 && u >= n / 2) break;
            if (n % 2 == 1 && u - ch >= n / 2) break;
            int d1 = k - 2 * u;
            int cor1 = max(u + d1 - 1, u + 1);
            int cor2 = min(u + k - 1, n - u - ch - 1);
            int p1 = lower_bound(cnt2[i].begin(), cnt2[i].end(), cor1) - cnt2[i].begin();
            int p2 = upper_bound(cnt2[i].begin(), cnt2[i].end(), cor2) - cnt2[i].begin();
            ans += max(0ll, p2 - p1);
        }
        //cout << i << " " << ans << endl;
    }
}
signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    algo(a, k, n);
    reverse(a.begin(), a.end());
    algo(a, k, n, 0);
    //cout << ans << endl;
    cout << (n - k + 1) * (k / 2) - ans << endl;
    return 0;
}
