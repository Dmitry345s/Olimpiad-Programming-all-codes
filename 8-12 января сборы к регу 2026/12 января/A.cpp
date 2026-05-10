#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    int ans = -1;
    for (int i = 0; i < (1 << 9); ++i) {
        int mul = 1;
        int c = 0;
        for (int j = 8; j >= 0; --j) {
            if ((i >> j) & 1) {
                mul *= (j + 1);
                c *= 10;
                c += j + 1;
            }
        }
        if (mul == n) ans = max(ans, c);
    }
    cout << ans << endl;
    return 0;
}
