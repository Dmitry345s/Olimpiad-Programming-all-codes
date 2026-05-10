#include<bits/stdc++.h>

using namespace std;

long long mod = 1e9 + 7;
int p = 31;

signed main() {
    string s;
    cin >> s;
    int n = s.size();
    vector<long long> ps(n);
    ps[0] = 1;
    for (int i = 1; i < n; ++i) {
        ps[i] = (ps[i - 1] * p) % mod;
    }
    vector<long long> h(n + 1);
    h[0] = 0;
    for (int i = 1; i < n + 1; ++i) {
        h[i] = (h[i - 1] * p + (int)s[i - 1] - 97 + 1) % mod;
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l1, r1, l2, r2;
        cin >> l1 >> r1 >> l2 >> r2;
        long long hash1 = (h[r1] - (h[l1 - 1] * ps[r1 - l1 + 1]) % mod + mod) % mod;
        long long hash2 = (h[r2] - (h[l2 - 1] * ps[r2 - l2 + 1]) % mod + mod) % mod;
        if (hash1 == hash2) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
