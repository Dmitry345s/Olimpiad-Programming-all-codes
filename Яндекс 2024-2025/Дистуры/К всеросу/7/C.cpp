#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i) {
        cin >> x[i];
    }
    int w, v;
    cin >> w >> v;
    vector<long double> ts(n);
    for (int i = 0; i < n; ++i) {
        ts[i] = (long double)x[i] / v;
    }
    //cout << ts.back() << endl;
    int q;
    cin >> q;
    cout.precision(20);
    cout << fixed;
    for (int i = 0; i < q; ++i) {
        int p, t, u;
        cin >> p >> t >> u;
        long double ans = (long double)(x.back() - p) / u + t;
        int j = lower_bound(x.begin(), x.end(), p) - x.begin();
        int j2 = j - 1;
        long double t1 = (long double)(x[j] - p) / u + t;
        //cout << t1 << endl;
        //cout << ts[0] << endl;
        int l = -1, r = 1e9;
        while (l + 1 < r) {
            //cout << l << " " << r << endl;
            int m = (l + r) / 2;
            if (t1 - ts[j] - w * m <= 0) {
                r = m;
            } else {
                l = m;
            }
        }
        //cout << r << endl;
        ans = min(ans, ts.back() + w * r);
        if (j2 >= 0) {
            long double t2 = (long double)(p - x[j2]) / u + t;
            int l = -1, r = 1e9;
            while (l + 1 < r) {
                int m = (l + r) / 2;
                if (t2 - ts[j2] - w * m <= 0) {
                    r = m;
                } else {
                    l = m;
                }
            }
            ans = min(ans, ts.back() + w * r);
        }
        cout << ans << endl;
    }
    return 0;
}
