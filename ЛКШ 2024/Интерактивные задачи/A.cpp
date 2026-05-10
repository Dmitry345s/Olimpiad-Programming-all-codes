#include<bits/stdc++.h>

using namespace std;

long long qs(long long x1, long long y1, long long x2, long long y2) {
    long long ans;
    cout << "? " << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
    cin >> ans;
    return ans;
}

signed main() {
    int n;
    cin >> n;
    long long ans = 0;
    ans = qs(1, 1, n, n);
    long long l = 0, r = n;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (qs(1, 1, n, m) < ans) {
            l = m;
        } else {
            r = m;
        }
    }
    long long y = r;
    l = 1, r = n + 1;
    while (l + 1 < r) {
        long long m = (l + r) / 2;
        if (qs(m, 1, n, n) < ans) {
            r = m;
        } else {
            l = m;
        }
    }
    long long x = l;
    long long v1 = qs(l, 1, l, n);
    cout << "! " << x << " " << y - v1 + 1 << " " << x + (ans / v1) - 1 << " " << y << endl;
    return 0;
}
