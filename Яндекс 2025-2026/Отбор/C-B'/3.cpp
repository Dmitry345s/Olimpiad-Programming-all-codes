#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    if (n > m) swap(n, m);
    if (n == 1) {
        if (m == 1) {
            cout << 1 << endl;
        } else {
            cout << m - 2 << endl;
        }
    } else {
        cout << (n - 2) * (m - 2) << endl;
    }
    return 0;
}
