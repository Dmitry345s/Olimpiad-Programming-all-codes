#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    array<int, 10> arr = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int l, r;
        cin >> l >> r;
        l--;
        int ans = (r / 9) * 45 + arr[r % 9] - (l / 9) * 45 - arr[l % 9];
        cout << ans << endl;
    }
}
