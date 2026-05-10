#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> ls(n - 1), rs(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> ls[i] >> rs[i];
    }
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, s, e;
            cin >> p >> s >> e;
            --p;
            ls[p] = s;
            rs[p] = e;
        } else {
            int a, b, c, d;
            cin >> a >> b >> c >> d;
            --a; --c;
            int now = b;
            int ans = 0;
            while (a != c) {
                if (a > c) {
                    --a;
                    if (now < rs[a]) {
                        now = max(now, ls[a]) + 1;
                    } else {
                        ans += now - rs[a] + 1;
                        now = rs[a];
                    }
                } else {
                    if (now < rs[a]) {
                        now = max(now, ls[a]) + 1;
                    } else {
                        ans += now - rs[a] + 1;
                        now = rs[a];
                    }
                    a++;
                }
            }
            if (now > d) {
                ans += now - d;
            }
            cout << ans << endl;
        }
    }
    return 0;
}
