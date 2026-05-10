#include<bits/stdc++.h>

using namespace std;

long long mod = 1e9 + 7;
int p = 179;

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<long long> ps(n + 1), h(n + 1);
    ps[0] = 1;
    for (int i = 1; i < n + 1; ++i) {
        ps[i] = (ps[i - 1] * p) % mod;
        h[i] = (h[i - 1] * p + (int)s[i - 1] - 97 + 1) % mod;
    }
    vector<long long> h2(n + 1);
    h2[n] = 0;
    for (int i = n - 1; i >= 0; --i) {
        h2[i] = (h2[i + 1] * p + (int)s[i] - 97 + 1) % mod;
    }
    long long ans = 0;
    for (int i = 1; i < n + 1; ++i) {
        int l = 0, r = min(i - 1, n - i) + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            long long hash1 = (h[i + m] - (h[i - m - 1] * ps[2 * m + 1]) % mod + mod) % mod;
            long long hash2 = (h2[i - m - 1] - (h2[i + m] * ps[2 * m + 1]) % mod + mod) % mod;
            if (hash1 == hash2) {
                l = m;
            } else {
                r = m;
            }
        }
        ans += l + 1;
        //cout << ans << endl;
    }
    for (int i = 1; i < n; ++i) {
        int l = 0, r = min(i, n - i) + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            int left = i - m, right = i + m;
            long long hash1 = (h[right] - (h[left] * ps[2 * m]) % mod + mod) % mod;
            long long hash2 = (h2[left] - (h2[right] * ps[2 * m]) % mod + mod) % mod;
            if (hash1 == hash2) {
                l = m;
            } else {
                r = m;
            }
        }
        ans += l;
    }
    cout << ans << endl;
    return 0;
}
