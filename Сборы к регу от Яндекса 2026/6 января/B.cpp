#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < q; ++i) {
        int x;
        cin >> x;
        if (x == 1) {
            cout << -1 << '\n';
            continue;
        }
        int f = 1;
        int u = x;
        for (int j = 2; j * j <= u; ++j) {
            if (x % j == 0) {
                f = j;
            }
            while (x % j == 0) {
                x /= j;
            }
        }
        if (x != 1) {
            f = x;
        }
        cout << n / f - 1 << '\n';
    }
    return 0;
}
