#include<bits/stdc++.h>

#define int long long

using namespace std;

bool check(int x, int a, int b) {
    double ch = (double)x / a + (double)x / b;
    return ch <= 1;
}

signed main() {
    int a, b;
    cin >> a >> b;
    if (a == 0 || b == 0) {
        cout << 0 << endl;
        return 0;
    }
    int l = 0, r = 1e9 + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(m, a, b)) {
            l = m;
        } else {
            r = m;
        }
    }
    cout << l << endl;
    return 0;
}
