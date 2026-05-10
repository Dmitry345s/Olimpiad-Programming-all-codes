#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    vector<int> h(n), c(n);
    vector<int> b;
    for (int i = 0; i < n; ++i) {
        cin >> h[i] >> c[i];
        b.push_back(h[i]);
    }
    sort(b.begin(), b.end());
    b.erase(unique(b.begin(), b.end()), b.end());
    for (int i = 0; i < n; ++i) {
        h[i] = lower_bound(b.begin(), b.end(), h[i]) - b.begin();
        //cout << h[i] << endl;
    }
    int x = (n / 2);
    vector<pair<int, int>> a;
    for (int i = 0; i < (1 << x); ++i) {
        int sum = 0;
        int flag = 1;
        int last = 0;
        for (int j = 0; j < x; ++j) {
            if ((i >> j) & 1) {
                if (h[j] >= last) {
                    last = h[j];
                    sum += c[j];
                } else {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag) {
            a.push_back({sum, last});
        }
    }
    vector<pair<int, int>> a2;
    for (int i = 0; i < (1 << (n - x)); ++i) {
        int sum = 0;
        int flag = 1;
        int last = n - 1;
        for (int j = n - 1; j >= x; --j) {
            if ((i >> (j - x)) & 1) {
                if (h[j] <= last) {
                    last = h[j];
                    sum += c[j];
                } else {
                    flag = 0;
                    break;
                }
            }
        }
        if (flag) {
            a2.push_back({sum, last});
        }
    }
    sort(a.begin(), a.end());
    sort(a2.begin(), a2.end());
    vector<int> tans(n);
    int ans = 0;
    int r = (int)a2.size() - 1;
    for (int i = 0; i < (int)a.size(); ++i) {
        //cout << a[i].first << " " << a[i].second << endl;
        while (r >= 0 && a2[r].first + a[i].first >= k) {
            tans[a2[r].second]++;
            r--;
        }
        for (int j = a[i].second; j < n; ++j) {
            ans += tans[j];
        }
    }
    cout << ans << endl;
    return 0;
}
