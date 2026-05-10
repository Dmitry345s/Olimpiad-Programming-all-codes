#include<bits/stdc++.h>

using namespace std;

signed main() {
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
    return 0;
}
