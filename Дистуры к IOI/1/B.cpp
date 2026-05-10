#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int P = 1e9 + 7;
const int MAX = 1e4;
ull pows[MAX];

int frad(string a) {
    int n = (int)a.size();
    string b = a;
    reverse(b.begin(), b.end());
    vector<ull> hs1(n + 1), hs2(n + 1);
    for (int i = 0; i < n; ++i) {
        hs1[i + 1] = hs1[i] * P + (a[i] - 'a' + 1);
        hs2[i + 1] = hs2[i] * P + (b[i] - 'a' + 1);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int l = 1, r = min(i + 1, n - i) + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            ull hl = hs1[i + 1] - hs1[i + 1 - m] * pows[m];
            int j = n - i - 1;
            ull hr = hs2[j + 1] - hs2[j + 1 - m] * pows[m];
            if (hl == hr) {
                l = m;
            } else {
                r = m;
            }
        }
        ans = max(ans, l);
    }
    return ans;
}

signed main() {
    pows[0] = 1;
    for (int i = 1; i < MAX; ++i) {
        pows[i] = pows[i - 1] * P;
    }
    int n, m;
    cin >> n >> m;
    vector<string> a(n);
    vector<string> b(m);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int j = 0; j < m; ++j) {
        cin >> b[j];
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            string now = a[i] + b[j];
            ans += frad(now);
        }
    }
    cout << ans << endl;
    return 0;
}
