#include<bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> ch(n + 1);
        vector<int> a(k);
        for (int i = 0; i < k; ++i) {
            cin >> a[i];
            ch[a[i]] = 1;
        }
        if (ch[1]) {
            cout << n << " " << k - 1 << endl;
            for (int i = 1; i < k; ++i) {
                cout << a[i] << " ";
            }
            cout << endl;
        } else {
            cout << n << " " << k + 1 << endl;
            cout << 1 << " ";
            for (int i = 0; i < k; ++i) {
                cout << a[i] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
