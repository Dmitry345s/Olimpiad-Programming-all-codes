#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    vector<array<int, 2>> a(3);
    for (int i = 0; i < 3; ++i) {
        cin >> a[i][0] >> a[i][1];
    }
    int ans = 1e18;
    for (int i = 0; i < 8; ++i) {
        vector<array<int, 2>> now = a;
        for (int j = 0; j < 3; ++j) {
            if ((i >> j) & 1) {
                swap(now[j][0], now[j][1]);
            }
        }
        sort(now.begin(), now.end());
        ans = min(ans, max(max(now[0][1], now[1][1]), now[2][1]) * (now[0][0] + now[1][0] + now[2][0]));
        do {
            int x = max(now[0][0] + now[1][0], now[2][0]);
            int y = max(now[0][1] + now[2][1], now[1][1]);
            if (now[2][0] <= now[0][0] || now[1][1] <= now[0][1]) {
                ans = min(ans, x * y);
            }
        } while (next_permutation(now.begin(), now.end()));
    }
    cout << ans << endl;
    return 0;
}
