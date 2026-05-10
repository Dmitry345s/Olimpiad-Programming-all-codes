#include<bits/stdc++.h>

using namespace std;

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int s, x;
        cin >> s >> x;
        int ans = 0;
        for (int a = 0; a <= s; ++a) {
            for (int b = 0; b <= s; ++b) {
                for (int c = 0; c <= s; ++c) {
                    if (a + b + c <= s && a * b * c <= x) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
