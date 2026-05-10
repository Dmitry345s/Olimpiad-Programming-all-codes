#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int x, y;
    cin >> x >> y;
    if (y % 1000 != 0 && y % 1000 != 500) {
        cout << -1 << endl;
        return 0;
    }
    int cnt1 = 0, cnt2 = 0, cnt3 = 0;
    if (y % 1000 == 500) {
        cnt3++;
        x--;
        y -= 2500;
    }
    if (x < 0 || y < 0) {
        cout << -1 << endl;
        return 0;
    }
    int u = y / 5000;
    y %= 5000;
    int u2 = y / 1000;
    y %= 1000;
    cnt3 += 2 * u;
    cnt2 += u2;
    cnt1 = x - 2 * u - u2;
    if (cnt1 < 0) {
        cout << -1 << endl;
        return 0;
    }
    cout << cnt1 << " " << cnt2 << " " << cnt3 << endl;
    return 0;
}

