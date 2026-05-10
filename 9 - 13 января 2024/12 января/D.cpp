#include<bits/stdc++.h>

//#define int long long

using namespace std;

//mt19937 rnd(time(0));

signed main() {
    int n;
    cin >> n;
    vector<vector<int>> f(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            char u;
            cin >> u;
            if (u == '1') {
                f[i][j] = 1;
            }
        }
    }
    vector<vector<int>> pref(n + 1, vector<int> (n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + f[i - 1][j - 1];
        }
    }
    vector<array<int, 4>> all;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int l = i; l < n; ++l) {
                for (int k = j; k < n; ++k) {
                    int sum1 = (l - i + 1) * (k - j + 1);
                    int sum2 = pref[l + 1][k + 1] + pref[i][j] - pref[l + 1][j] - pref[i][k + 1];
                    if (sum1 == sum2) {
                        all.push_back({i, j, l, k});
                        //cout << i << " " << j << " " << l << " " << k << endl;
                    }
                }
            }
        }
    }
    long long ans = 0;
    int mod = 1e9 + 7;
    for (int i = 0; i < (int)all.size(); ++i) {
        for (int j = 0; j < (int)all.size(); ++j) {
            if (all[i][0] > all[j][2] || all[i][3] < all[j][1] || all[j][0] > all[i][2] || all[j][3] < all[i][1]) {
                ans += 1;
                //cout << i << " " << j << endl;
            }
        }
    }
    cout << ans % mod << endl;
    return 0;
}
