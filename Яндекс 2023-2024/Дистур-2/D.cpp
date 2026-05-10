#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (int i = 0; i < m; ++i) {
        string t;
        cin >> t;
        int c = t.size();
        int p = 1;
        for (int j = 0; j < c; ++j) {
            if (t[j] == '?') {
                p *= 10;
            }
        }
        int ans = 0;
        for (int j = 0; j < p; ++j) {
            int now = 0;
            int copy_p = j;
            for (int l = 0; l < c; ++l) {
                if (t[l] == '?') {
                    now *= 10;
                    now += copy_p % 10;
                    copy_p /= 10;
                } else {
                    now *= 10;
                    now += t[l] - '0';
                }
            }
            ans += n - (lower_bound(a.begin(), a.end(), now) - a.begin());
        }
        cout << ans << endl;
    }
    return 0;
}
