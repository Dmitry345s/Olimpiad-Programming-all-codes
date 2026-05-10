#include<bits/stdc++.h>

using namespace std;

long long MOD = 1e18;
const long long INF = 1e18;

long long mod(long long x) {
    return ((x % MOD) + MOD) % MOD;
}

signed main() {
    long long x, m;
    cin >> x >> m;
    MOD -= m;
    cout << "? " << 1 << endl;
    long long y;
    cin >> y;
    long long whr = (x + INF - y) % INF + 1;
    long long l = -501, r = 1;
    while (l + 1 < r) {
        long long c = (l + r) / 2;
        cout << "? " << mod(whr + c) + 1 << endl;
        cin >> y;
        if (y == x) {
            cout << "! " << mod(whr + c) + 1 << endl;
            return 0;
        }
        if (y - x < INF / 2 && (y > x || x - y > INF / 2)) {
            r = c;
        } else {
            l = c;
        }
    }
    cout << "! " << -1 << endl;
    return 0;
}
