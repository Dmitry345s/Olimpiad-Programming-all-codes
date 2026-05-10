#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<int> a(m);
    for(int i = 0; i < n; ++i) {
        int b;
        cin >> b;
        b--;
        a[b]++;
    }
    vector<pair<int, int>> c;
    for (int i = 0; i < m; ++i) {
        c.push_back({a[i], i});
    }
    sort(c.begin(), c.end());
    vector<int> pref(m + 1);
    vector<int> pref2(m + 1);
    for (int i = 1; i <= m; ++i) {
        pref[i] = pref[i - 1] + c[i - 1].first;
        pref2[i] = c[i - 1].first * (i - 1) - pref[i - 1];
    }
    for (int i = 0; i < q; ++i) {
        vector<int> fans;
        int k;
        cin >> k;
        k -= n;
        bool flag = 1;
        for (int j = 1; j < m + 1; ++j) {
            if (pref2[j] >= k) {
                k -= pref2[j - 1];
                flag = 0;
                break;
            }
            fans.push_back(c[j - 1].second);
        }
        if (flag) {
            k -= pref2.back();
        }
        sort(fans.begin(), fans.end());
        int mod = fans.size();
        k %= mod;
        if (k == 0) {
            k = (long long)(fans.size()) - 1;
        } else {
            k--;
        }
        cout << fans[k] + 1 << endl;
    }
    return 0;
}
