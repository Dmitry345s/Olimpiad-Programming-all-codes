#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int t;
    cin >> t;
    while (t--) {
        long long x;
        cin >> x;
        vector<int> c;
        for (int i = 0; i < 62; ++i) {
            if ((x >> i) & 1) {
                c.push_back(i);
            }
        }
        if (x < 7) {
            cout << -1 << endl;
            continue;
        }
        long long p = 1;
        if (c.size() >= 3) {
            int k = c.size();
            cout << (p << c[k - 1]) + (p << c[k - 2]) + (p << c[k - 3]) << endl;
        } else {
            if (c.size() == 1 || c[0] < 2) {
               cout << (p << (c.back() - 1)) + (p << (c.back() - 2)) + (p << (c.back() - 3)) << endl;
            } else {
                cout << (p << c.back()) + (p << (c[0] - 1)) + (p << (c[0] - 2)) << endl;
            }
        }
    }
    return 0;
}
