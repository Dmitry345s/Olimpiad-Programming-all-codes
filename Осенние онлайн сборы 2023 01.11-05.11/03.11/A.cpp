#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, a, b, c;
    cin >> n >> a >> b >> c;
    __int128 ans = 0;
    if (b - c < a && n >= b) {
        ans += (n - b) / (b - c) + 1;
    }
    __int128 x = n - ans * (b - c);
    ans += x / a;
    cout << max((int)ans, (int)0) << endl;
    return 0;
}
