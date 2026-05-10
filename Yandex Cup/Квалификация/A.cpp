#include<bits/stdc++.h>

using namespace std;

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        int in = -1;
        for (int k = 1; k * k <= n + m; ++k) {
            if (k * k == n + m) {
                in = k;
            }
        }
        if (in == -1) {
            cout << "NO" << endl;
            continue;
        }
        int k = in;
        if (n % k % 2 && m % k % 2) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
}
