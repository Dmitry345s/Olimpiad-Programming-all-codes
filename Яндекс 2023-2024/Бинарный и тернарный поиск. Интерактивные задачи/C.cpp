#include<bits/stdc++.h>

using namespace std;

int ask(int i, int & x) {
    cout << "? " << i << endl;
    cin >> x;
    int x1;
    cout << "? " << i + 1 << endl;
    cin >> x1;
    if (x1 - x > 0) {
        return 0;
    } else {
        return 1;
    }
}

signed main() {
    int n, k;
    cin >> n >> k;
    int l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int x;
        int ch = ask(m, x);
        if (ch) {
            r = m;
        } else {
            if (x > k) {
                r = m;
            } else {
                l = m;
            }
        }
    }
    if (l) {
        int u;
        int p = ask(l, u);
        if ((p || !p) && u == k) {
            cout << "! " << l << endl;
            return 0;
        }
    }
    l = 0, r = n;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        int x;
        int ch = ask(m, x);
        if (!ch) {
            l = m;
        } else {
            if (x < k) {
                r = m;
            } else {
                l = m;
            }
        }
    }
    if (l) {
        int u;
        int p = ask(l, u);
        if ((p || !p) && u == k) {
            cout << "! " << l << endl;
            return 0;
        }
    }
    cout << "! " << r << endl;
    return 0;
}
