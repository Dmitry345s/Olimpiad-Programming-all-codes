#include<iostream>
#include<vector>
#include<string>

using namespace std;

long long mod = 1e9 + 7, mod2 = 1791791791;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<long long> h(n), h2(n), pows(n), pows2(n);
    pows[0] = 1;
    pows2[0] = 1;
    int p = 31;
    for (int i = 1; i < n; ++i) {
        pows[i] = (pows[i - 1] * p) % mod;
        pows2[i] = (pows2[i - 1] * p) % mod2;
    }
    h[0] = s[0] - 'a' + 1;
    h2[0] = s[0] - 'a' + 1;
    for (int i = 1; i < n; ++i) {
        h[i] = h[i - 1] + ((s[i] - 'a' + 1) * pows[i]) % mod;
        h2[i] = h2[i - 1] + ((s[i] - 'a' + 1) * pows2[i]) % mod2;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b; --c; --d;
        if (b - a != d - c) {
            cout << "No" << endl;
            continue;
        }
        long long hash1 = h[b];
        if (a > 0) {
            hash1 -= h[a - 1];
        }
        hash1 = (hash1 + mod) % mod;
        long long hash2 = h[d];
        if (c > 0) {
            hash2 -= h[c - 1];
        }
        hash2 = (hash2 + mod) % mod;
        long long hash3 = h2[b];
        if (a > 0) {
            hash3 -= h2[a - 1];
        }
        hash3 = (hash3 + mod2) % mod2;
        long long hash4 = h2[d];
        if (c > 0) {
            hash4 -= h2[c - 1];
        }
        hash4 = (hash4 + mod2) % mod2;
        if ((a < c && (hash1 * pows[c - a]) % mod == hash2
             || c <= a && hash1 == hash2 * pows[a - c] % mod) &&
            (a < c && (hash3 * pows2[c - a]) % mod2 == hash4
             || c <= a && hash3 == hash4 * pows2[a - c] % mod2)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
