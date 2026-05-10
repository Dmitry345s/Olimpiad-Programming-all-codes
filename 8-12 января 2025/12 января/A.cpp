#include<bits/stdc++.h>

#define int long long

using namespace std;

int ch(vector<int> a, vector<int> h, int x) {
    int ans = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        ans += abs(h[i] - x) * a[i];
    }
    return ans;
}
signed main() {
    int n;
    cin >> n;
    vector<int> a(n), h(n);
    for (int i = 0; i < n; ++i) cin >> h[i];
    for (int i = 0; i < n; ++i) cin >> a[i];
    int l = 0, r = 1e6 + 1;
    while (l + 2 < r) {
        int m = (l + r) / 2;
        int m2 = m++;
        //cout << m << " " << m2 << endl;
        if (ch(a, h, m2) < ch(a, h, m)) {
            r = m;
        } else {
            l = m2;
        }
    }
    int ans = l;
    if (ch(a, h, l + 1) < ch(a, h, l)) {
        ans = l + 1;
    }
    cout << ans << " " << ch(a, h, ans) << endl;
    return 0;
}
