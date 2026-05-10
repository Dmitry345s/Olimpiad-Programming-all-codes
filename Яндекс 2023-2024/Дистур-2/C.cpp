#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int MAXM = 4e3 + 1;
    vector<vector<int>> bag(n + 1, vector<int> (MAXM));
    bag[0][0] = 1;
    int mod = 1e9 + 7;
    int cnt = 0;
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        int cnt2 = 0;
        int del = 0;
        for (int j = 0; j < MAXM; ++j) {
            if (j > a[i - 1]) {
                cnt2 += bag[i - 1][j];
                cnt2 %= mod;
            }
            bag[i][j] += bag[i - 1][j];
            bag[i][j] %= mod;
            if (a[i - 1] + j < MAXM) {
                bag[i][j + a[i - 1]] += bag[i - 1][j];
                bag[i][j + a[i - 1]] %= mod;
            } else {
                del += bag[i - 1][j];
                del %= mod;
            }
        }
        ans += (cnt + cnt2) % mod;
        ans %= mod;
        cnt = (cnt * 2 % mod + del) % mod;
    }
    cout << ans << endl;
    return 0;
}
