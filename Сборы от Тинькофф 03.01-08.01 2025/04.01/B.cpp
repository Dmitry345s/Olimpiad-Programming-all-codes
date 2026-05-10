#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    k = k - m;
    int a, b, c;
    cin >> a >> b >> c;
    swap(b, c);
    int t;
    cin >> t;
    vector<int> s(m);
    for (int i = 0; i < m; ++i) {
        cin >> s[i];
    }
    vector<int> bl(m - 1);
    for (int i = 0; i < m - 1; ++i) {
        bl[i] = s[i];
    }
    for (int i = 0; i < m - 1; ++i) {
        bl[i] = min(s[i + 1] - 1, bl[i] + max(0ll, t - ((s[i] - 1) * c + (bl[i] - s[i]) * b)) / a);
    }
    for (int _ = 0; _ < k; ++_) {
        int maxm = 0, in = 0;
        for (int i = 0; i < m - 1; ++i) {
            int x = min(max(0ll, t - ((s[i] - 1) * c + (bl[i] + 1 - s[i]) * b) + a) / a, s[i + 1] - 1 - bl[i]);
            if (x >= maxm) {
                maxm = x;
                in = i;
            }
        }
        int x = min(max(0ll, t - ((s[in] - 1) * c + (bl[in] + 1 - s[in]) * b) + a) / a, s[in + 1] - 1 - bl[in]);
        bl[in] = bl[in] + x;
    }
    int ans = 0;
    for (int i = 0; i < m - 1; ++i) {
        ans += (bl[i] - s[i] + 1);
        //cout << bl[i] << " ";
        if ((s[i] - 1) * c > t) ans--;
    }
    //cout << endl;
    if ((s.back() - 1) * c <= t) ans++;
    cout << ans - 1 << endl;
    return 0;
}
