#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n;
    cin >> n;
    long long l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        long long p;
        cout << "? " << 1 << " " << 1 << " " << m << " " << n << endl;
        cin >> p;
        if (p) {
            r = m;
        } else {
            l = m;
        }
    }
    int v1;
    int x = r;
    cout << "? " << 1 << " " << 1 << " " << r << " " << n << endl;
    cin >> v1;
    l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        long long p;
        cout << "? " << 1 << " " << 1 << " " << n << " " << m << endl;
        cin >> p;
        if (p) {
            r = m;
        } else {
            l = m;
        }
    }
    int v2;
    int y = r;
    cout << "? " << 1 << " " << 1 << " " << n << " " << r << endl;
    cin >> v2;
    cout << "! " << x << " " << y << " " << x + v2 - 1 << " " << y + v1 - 1 << endl;
    return 0;
}
