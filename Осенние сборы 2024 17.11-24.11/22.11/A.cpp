#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<int> a(n);
    for (int i = 0; i < k; ++i) {
        cin >> a[i];
    }
    vector<int> b(n);
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<vector<int>> nums(n);
    for (int i = 0; i < m; ++i){
        for (int j = 0; j < n; ++j) {
            int u;
            cin >> u;
            --u;
            nums[u].push_back(a[j]);
        }
    }
    vector<int> now(n);
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        sort(nums[i].rbegin(), nums[i].rend());
        for (int j = 0; j < m - s; ++j) {
            cnt[i] += nums[i][j];
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        int l = m - s;
        int ch1 = cnt[u] + b[u];
        int ch2 = cnt[v] + b[v];
        //cout << ch1 << " " << ch2 << endl;
        while (l < m && ch1 >= ch2) {
            ch1 += nums[u][l];
            ch2 += a[0];
            l++;
        }
        //cout << l << " " << ch1 << " " << ch2 << endl;
        if (ch1 < ch2) {
            cout << l - m + s << '\n';
        } else {
            cout << s + (ch1 - ch2) / (a[0] - a[n - 1]) + 1 << '\n';
        }
    }
    return 0;
}
