#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    int ans = 0;
    int rans = -1;
    int wm = m;
    for (int ans = n; ans >= 1; --ans) {
        if (a[n - ans] >= ans - 1 && wm >= (ans - 1) * ans / 2) {
            m = wm;
            vector<int> b = a;
            multiset<int> now;
            for (int i = n - 1; i >= n - ans; --i) {
                b[i] -= ans - 1;
            }
            for (int i = 0; i < n; ++i) {
                now.insert(-b[i]);
            }
            m -= (ans * (ans - 1)) / 2;
            while (m >= 0 && (int)now.size() > 1) {
                int v = -*now.begin();
                now.erase(now.begin());
                int u = -*now.begin();
                now.erase(now.begin());
                if (v == 0 || u == 0) break;
                --v; --u;
                m--;
                now.insert(-v);
                now.insert(-u);
            }
            if (m <= 0) {
                cout << ans << endl;
                return 0;
            }
        }
    }
    cout << -1 << endl;
    return 0;
}
