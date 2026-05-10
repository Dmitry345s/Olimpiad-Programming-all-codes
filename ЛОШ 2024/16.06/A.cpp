#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, a, b;
    cin >> n >> a >> b;
    if (a > b) {
        cout << n * a << endl;
    } else {
        int r = (b - a);
        int sum = r * (r + 1) / 2;
        if (r > n) {
            cout << n * (b - n) + n * (n + 1) / 2 << endl;
            return 0;
        }
        cout << n * a + sum << endl;
    }
    return 0;
}
