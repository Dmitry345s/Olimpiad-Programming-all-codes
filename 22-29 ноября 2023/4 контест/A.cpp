#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int p, n, m;
    cin >> p >> n >> m;
    int ch = n * 5 + n * 3 * 3 + m * 10 + m * 4 * 3;
    int cnt = n * 3 + m * 4;
    if (ch >= p) {
        cout << cnt << endl;
    } else {
        cout << cnt + (p - ch + 2) / 3 << endl;
    }
    return 0;
}
