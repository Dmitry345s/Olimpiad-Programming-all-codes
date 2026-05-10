#include<bits/stdc++.h>

#define int long long

using namespace std;

int mod = 1e9 + 7;

long long get(int x, int h2) {
    if (x == 1) {
        return 3;
    }
    if (x == 0) {
        return 1;
    }
    if (x == -1) {
        return 0;
    }
    vector<int> pows(100);
    pows[0] = 1;
    for (int i = 1; i < 100; ++i) {
        pows[i] = (pows[i - 1] * 3) % mod;
    }
    int ans = 0;
    for (int h = h2; h > 0; --h) {
        if ((x >> h) & 1) {
            ans += pows[h];
            ans %= mod;
            x -= (1ll << h);
            ans += (get(x, h2 - 1) * 2) % mod;
            ans %= mod;
            return ans;
        }
    }
    return 0;
}

signed main() {
    int a, b, c, d;
    cin >> a >> b >> c >> d;
    /*if (a == 0 && c == 0 && d == (int)1e18) {
        int w = 0;
        while (b > (1ll << w) - 1) {
            w++;
        }
        int ans = 1;
        for (int i = 0; i < w; ++i) {
            ans *= 3;
            ans %= mod;
        }
        cout << ans << endl;
        return 0;
    }*/
    if (c == 0 && (int)d == 1e18) {
        long long ans = ((get(b, 60) - get(a - 1, 63)) % mod + mod) % mod;
        cout << ans << endl;
        return 0;
    }
    int ans = 0;
    for (int i = a; i <= b; ++i) {
        for (int j = c; j <= d; ++j) {
            if ((i ^ j) == ((i ^ j) & i)) {
                ans += 1;
            }
        }
    }
    cout << ans << endl;
    return 0;
}
