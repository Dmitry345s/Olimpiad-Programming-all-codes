#include<bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        int flag = 0;
        for (int i = 0; i < n; ++i) {
            cin >> a[i];
            if (a[i] != 1) flag = 1;
        }
        if (n % 2 == 0 && !flag) {
            cout << "SECOND" << endl;
        } else {
            cout << "FIRST" << endl;
        }
    }
    return 0;
}
