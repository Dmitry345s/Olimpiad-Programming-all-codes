#include<bits/stdc++.h>

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int now_xor = 0;
        for (int i = 0; i < n; ++i) {
            cout << (i ^ now_xor) << endl;
            int r;
            cin >> r;
            if (r == 0) {
                now_xor = (now_xor ^ (now_xor ^ i));
            }
        }
    }
    return 0;
}
