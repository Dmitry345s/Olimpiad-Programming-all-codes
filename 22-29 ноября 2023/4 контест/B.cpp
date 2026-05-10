#include<bits/stdc++.h>

#define int long long
using ull = unsigned long long;

using namespace std;

signed main() {
    int n, k;
    cin >> n >> k;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    const int MAX = 501;
    char f[MAX][MAX];
    int rf[MAX][MAX];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> f[i][j];
            if (f[i][j] == 'b') {
                rf[i][j] = 1;
            } else {
                rf[i][j] = 0;
            }
        }
    }
    ull b = 11;
    ull pows[501 * 501];
    pows[0] = 1;
    for (int i = 1; i < 501 * 501; ++i) {
        pows[i] = pows[i - 1] * b;
    }
    map<ull, int> mp;
    ull h1[MAX];
    ull h2 = 0;
    for (int i = 0; i < k; ++i) {
        h2 += pows[i];
    }
    for (int j = 0; j < n - k + 1; ++j) {
        for (int i = 0; i < k; ++i) {
            for (int l = j + 1; l < j + k; ++l) {
                if (i == 0) {
                    h1[l - j] = (rf[i][l] ^ rf[i][j]);
                    continue;
                }
                h1[l - j] = (h1[l - j] * b + (rf[i][l] ^ rf[i][j]));
            }
        }
        for (int i = 0; i < n - k + 1; ++i) {
            ull h3 = 0;
            for (int l = j + 1; l < j + k; ++l) {
                ull geth;
                if (!(rf[i][l] ^ rf[i][j])) {
                    geth = h1[l - j];
                    h3 = h3 + geth * pows[(l - j) * k];
                } else {
                    geth = h2 - h1[l - j];
                    h3 = h3 + geth * pows[(l - j) * k];
                }
                h1[l - j] -= (rf[i][l] ^ rf[i][j]) * pows[k - 1];
                if (i == n - k) continue;
                h1[l - j] = h1[l - j] * b + (rf[i + k][l] ^ rf[i + k][j]);
            }
            ///cout << i << " " << j << " " << h3 << endl;
            mp[h3] += 1;
        }
    }
    long long ans = 0;
    long long prefs = 0;
    for (auto [key, val] : mp) {
        ans += prefs * val;
        prefs += val;
    }
    cout << ans << '\n';
    return 0;
}
