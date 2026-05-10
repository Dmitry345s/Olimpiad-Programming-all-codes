#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    int now = 10;
    int ans = 0;
    for (int i = 1; i < n; ++i) {
        if (i >= now) {
            now *= 10;
        }
        //cout << now << endl;
        if (i * now + i > n) {
            ans = i - 1;
            break;
        }
    }
    cout << ans << endl;
    return 0;
}
