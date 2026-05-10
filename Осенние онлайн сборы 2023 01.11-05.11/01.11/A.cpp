#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, k, x;
    cin >> n >> k >> x;
    int l = x / (n - k);
    if (x % (n - k)) {
        l += 1;
    }
    long long ans = x + l * k;
    cout << ans << endl;
    return 0;
}
