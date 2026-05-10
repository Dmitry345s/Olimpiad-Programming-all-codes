#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    if (n == k) {
        vector<int> ans(m);
        for (int i = 0; i < n; ++i) {
            ans[a[i]] = 1;
        }
        for (int i = 0; i < m; ++i) {
            cout << ans[i] << " ";
        }
        return 0;
    }
    int now = k;
    vector<int> sts;
    sts.push_back(0);
    while (now != 0) {
        sts.push_back(now);
        now = (now + k) % n;
    }
    sort(sts.begin(), sts.end());
    vector<int> ans(m);
    vector<int> last(m, -1);
    for (int i = 0; i < k; ++i) {
        last[a[i]] = i;
    }
    for (int i = k; i < n + k; ++i) {
        int ri = i % n;
        int x = (ri - k + n) % n;
        int j = upper_bound(sts.begin(), sts.end(), ri) - sts.begin();
        //cout << ri << " " << x << " " << j << endl;
        if (ri < k) {
            if (last[a[ri]] < ri) {
                x = min(x, last[a[ri]]);
            } else {
                x = max(x, last[a[ri]]);
            }
            int l = upper_bound(sts.begin(), sts.end(), x) - sts.begin();
            if (x > ri) {
                ans[a[ri]] += sts.size() - l + j;
            } else {
                ans[a[ri]] += j - l;
            }
            /*if (k == n && x == ri) {
                ans[a[ri]] += 1;
            }*/
        } else {
            x = max(x, last[a[ri]]);
            int l = upper_bound(sts.begin(), sts.end(), x) - sts.begin();
            ans[a[ri]] += j - l;
        }
        last[a[ri]] = ri;
    }
    for (int i = 0; i < m; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
