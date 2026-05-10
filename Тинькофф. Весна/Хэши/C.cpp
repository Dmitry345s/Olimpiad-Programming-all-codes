#include<iostream>
#include<vector>
#include<string>

using namespace std;

long long mod = 1e9 + 7, mod2 = 1e9 + 9;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<long long> pows(n), pows2(n);
    pows[0] = 1;
    pows2[0] = 1;
    int p = 31;
    for (int i = 1; i < n; ++i) {
        pows[i] = (pows[i - 1] * p) % mod;
        pows2[i] = (pows2[i - 1] * p) % mod2;
    }
    vector<long long> h(n), h2(n), h3(n), h4(n);
    h[0] = int(s[0]) - 97 + 1;
    h2[n - 1] = int(s[n - 1]) - 97 + 1;
    for (int i = 1; i < n; ++i) {
        h[i] = (h[i - 1] + (int(s[i]) - 97 + 1) * pows[i]) % mod;
        h2[n - i - 1] = (h2[n - i] + (int(s[n - i - 1]) - 97 + 1) * pows[i]) % mod;
        h3[i] = (h3[i - 1] + (int(s[i]) - 97 + 1) * pows2[i]) % mod2;
        h4[n - i - 1] = (h4[n - i] + (int(s[n - i - 1]) - 97 + 1) * pows2[i]) % mod2;
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        int l = 0, r = min(i, n - i - 1);
        int cnt = 0;
        while (l + 1 <= r && cnt < 30) {
            int m = (l + r + 1) / 2;
            long long hash1 = (h[i + m] - h[i] + mod) % mod, hash2 = (h2[i - m] - h2[i] + mod) % mod;
            long long hash3 = (h3[i + m] - h3[i] + mod2) % mod2, hash4 = (h4[i - m] - h4[i] + mod2) % mod2;
            if ((hash1 * pows[n - 1 - i]) % mod == (hash2 * pows[i]) % mod
                && (hash3 * pows2[n - 1 - i]) % mod2 == (hash4 * pows2[i]) % mod2) {
                l = m;
            } else {
                r = m;
            }
            cnt += 1;
        }
        ans += 1 + l;
    }
    for (int i = 0; i < n - 1; ++i) {
        int l = 0, r = min(i + 1, n - i - 1);
        int cnt = 0;
        while (l + 1 <= r && cnt < 30) {
            int m = (l + r + 1) / 2;
            long long hash1 = (h[i + m] - h[i] + mod) % mod, hash2 = (h2[i - m + 1] - h2[i + 1] + mod) % mod;
            long long hash3 = (h3[i + m] - h3[i] + mod2) % mod2, hash4 = (h4[i - m + 1] - h4[i + 1] + mod2) % mod2;
            if ((hash1 * pows[n - 1 - i]) % mod == (hash2 * pows[i + 1]) % mod
                && (hash3 * pows2[n - i - 1]) % mod2 == (hash4 * pows2[i + 1]) % mod2) {
                l = m;
            } else {
                r = m;
            }
            cnt += 1;
        }
        ans += l;
    }
    cout << ans << endl;
    return 0;
}
