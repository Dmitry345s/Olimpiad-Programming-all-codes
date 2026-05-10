#include<bits/stdc++.h>

using namespace std;

int ask(int i) {
    int p1, p2;
    cout << "? " << i << endl;
    cin >> p1;
    cout << "? " << i + 1 << endl;
    cin >> p2;
    if (i % 2 == 0) {
        if (p1 == p2) {
            return 1;
        } else {
            return 0;
        }
    } else {
        if (p1 == p2) {
            return 0;
        } else {
            return 1;
        }
    }
}

signed main() {
    int n;
    cin >> n;
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int ch = ask(m);
        if (ch) {
            r = m;
        } else {
            l = m;
        }
    }
    int ans;
    cout << "? " << r << endl;
    cin >> ans;
    cout << "! " << ans << endl;
    return 0;
}
