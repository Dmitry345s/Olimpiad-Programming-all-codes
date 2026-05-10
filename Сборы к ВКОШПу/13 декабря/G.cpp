#include<bits/stdc++.h>

using namespace std;

#define int long long

signed main() {
    int n, a, b, d;
    cin >> n >> a >> b;
    d = b - a;
    if (d % 2 == 0) {
        cout << d / 2 << endl;
        return 0;
    }
    cout << d / 2 + 1 + min(a - 1, n - b) << endl;
    return 0;
}
