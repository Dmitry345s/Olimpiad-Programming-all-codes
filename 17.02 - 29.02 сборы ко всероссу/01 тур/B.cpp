#include<bits/stdc++.h>

#define int long long

using namespace std;

int get(vector<int> & a) {
    int n = a.size();
    vector<int> dp(n + 1, 2e9);
    dp[0] = 0;
    for (int i = 0; i < n; ++i) {
        int j = upper_bound(dp.begin(), dp.end(), a[i]) - dp.begin();
        if (dp[j - 1] < a[i]) {
            dp[j] = a[i];
        }
    }
    for (int i = n; i >= 0; --i) {
        if (dp[i] != 2e9) {
            return i;
        }
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    vector<int> ans(n);
    vector<int> ls(n), rs(n);
    for (int i = 0; i < n; ++i) {
        cin >> ls[i] >> rs[i];
    }
    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> left, right;
        for (int j = 0; j < n; ++j) {
            if (ls[j] < ls[i] && rs[j] > ls[i] && rs[j] < rs[i]) {
                left.push_back({ls[j], rs[j]});
            }
            if (ls[j] > ls[i] && ls[j] < rs[i] && rs[j] > rs[i]) {
                right.push_back({rs[j], ls[j]});
            }
        }
        sort(left.begin(), left.end());
        sort(right.begin(), right.end());
        vector<int> to_get;
        for (int j = 0; j < right.size(); ++j) {
            to_get.push_back(right[j].second);
        }
        for (int j = 0; j < left.size(); ++j) {
            to_get.push_back(left[j].second);
        }
        ans[i] = get(to_get) + 1;
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        cout << ans[x - 1] << '\n';
    }
    return 0;
}
