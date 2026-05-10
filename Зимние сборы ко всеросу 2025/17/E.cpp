#include<bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    if (t == 1) {
        int n;
        cin >> n;
        int l = 0, r = n + 1;
        while (l + 1 < r) {
            int m = (l + r) / 2;
            cout << m << endl;
            int ans;
            cin >> ans;
            if (ans == 0) {
                //cout << "! " << m << endl;
                return 0;
            }
            if (ans == 1) {
                l = m;
            } else {
                r = m;
            }
        }
    } else {
        int n;
        cin >> n;
        int l = 0, r = n + 1;
        int q;
        cin >> q;
        for (int i = 0; i < q; ++i) {
            int a;
            cin >> a;
            int m = (l + r) / 2;
            if (a == 0) {
                cout << m << endl;
                return 0;
            }
            if (a == 1) {
                l = m;
            } else {
                r = m;
            }
        }
    }
    return 0;
}
