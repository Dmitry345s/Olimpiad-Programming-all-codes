#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    vector<int> used(n);
    int mn = 0;
    for (int i = 0; i < n; ++i) {
        mn = max(mn, a[i]);
        if (mn > a[i]) {
            used[i] = 1;
        }
    }
    int mx = n + 1;
    for (int i = n - 1; i >= 0; --i) {
        mx = min(mx, a[i]);
        if (mx < a[i]) {
            used[i] = 1;
        }
    }
    while (n > 0 && used.back() == 0) {
        used.pop_back();
        n--;
    }
    reverse(used.begin(), used.end());
    while (n > 0 && used.back() == 0) {
        used.pop_back();
        n--;
    }
    reverse(used.begin(), used.end());
    if (n == 0) {
        cout << 0 << endl;
        return 0;
    }
    int l = 0;
    vector<int> bl;
    while (l < n) {
        int st = l;
        while (l < n && used[l] == used[st]) {
            l++;
        }
        bl.push_back(l - st);
    }
    vector<int> dp((int)bl.size() + 1, n);
    vector<int> pref((int)bl.size() + 1);
    pref[0] = 0;
    for (int i = 0; i < (int)bl.size(); ++i) {
        pref[i + 1] = pref[i] + bl[i];
    }
    dp[0] = 0;
    for (int i = 1; i < (int)dp.size(); ++i) {
        if (i % 2 == 0) {
            dp[i] = dp[i - 1];
            continue;
        }
        for (int j = 0; j < min(i, 300); j += 2) {
            dp[i] = min(dp[i], dp[j] + (int)sqrt(pref[i] - pref[j]));
        }
        for (int j = i - 1; j >= max(0, i - 301); j -= 2) {
            dp[i] = min(dp[i], dp[j] + (int)sqrt(pref[i] - pref[j]));
        }
    }
    cout << dp.back() << endl;
    return 0;
}
