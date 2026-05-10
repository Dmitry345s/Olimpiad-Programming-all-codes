#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while(_--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        int add = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            add += a[i];
        }
        int nans = 0;
        int rans = 0;
        int jsum = 0;
        for (int i = 0; i < k; ++i) {
            nans += a[i] * (k - i);
            jsum += a[i];
        }
        rans = nans;
        for (int now = 1; now < n; ++now) {
            nans -= a[now - 1] * k;
            jsum -= a[now - 1];
            jsum += a[(now - 1 + k) % n];
            nans += jsum;
            rans = max(rans, nans);
        }
        cout << rans + add << endl;
    }
    return 0;
}
