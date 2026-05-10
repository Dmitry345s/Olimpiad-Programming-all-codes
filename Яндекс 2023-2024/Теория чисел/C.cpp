#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, a, b;
    cin >> a >> b >> n >> m;
    int c = a - b;
    int cl = (c % n + n) % n;
    for (int i = 0; i < n; ++i) {
        if (i * m % n == cl) {
            cout << i * m + b << endl;
        }
    }
    return 0;
}
