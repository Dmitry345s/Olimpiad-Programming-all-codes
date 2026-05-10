#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 2) cnt++;
    }
    vector<int> ls(n, -1);
    int now = -1;
    for (int i = 0; i < n; ++i) {
        if (a[i] == 2) now = i;
        ls[i] = now;
    }
    now = n;
    vector<int> pref(n, n);
    for (int i = n - 1; i >= 0; --i) {
        if (a[i] == 2) now = i;
        pref[i] = now;
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        if (a[i] == 2) {
            ans[i] = cnt;
        } else {
            int dif = i - ls[i] + pref[i] - i - 1;
            //cout << i << " " << dif << endl;
            if (i != 0 && a[i - 1] == 2 || i < n - 1 && a[i + 1] == 2) {
                dif = 1;
            }
            ans[i] = cnt + dif;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        --u; --v;
        --l;
        cout << ans[u] << '\n';
    }
    return 0;
}
