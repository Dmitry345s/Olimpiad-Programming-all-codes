#include<bits/stdc++.h>

///# define int long long

using namespace std;

const int LG = 61;

long long get(long long x) {
    long long ans = 0;
    for (long long i = 2; i < LG; ++i) {
        ans += (1ll << i) * ((x % (1ll << i)) % 2) * ((x >> i) & 1);
    }
    int y = x % 4;
    if (y == 2) ans += 1;
    if (y == 3) ans += 3;
    return ans;
}

signed main() {
    int n;
    cin >> n;
    long long ans = 0;
    vector<pair<long long, long long>> a(n);
    for (int i = 0; i < n; ++i) {
        long long l, r;
        cin >> l >> r;
        ans ^= get(r + 1);
        ans ^= get(l);
        a[i] = {l, r};
    }
    if (ans == 0) {
        cout << "Lose" << endl;
        return 0;
    }
    cout << "Win" << endl;
    int x = 0;
    for (int i = 0; i < LG; ++i) {
        if ((ans >> i) & 1) {
            x = i;
        }
    }
    for (int i = 0; i < n; ++i) {
        auto [l, r] = a[i];
        if ((l >> x) & 1) {
            cout << l << " " << (l ^ ans) << endl;
            return 0;
        }
        long long u = (((l >> x) ^ 1) << x);
        if (u <= r) {
            cout << u << " " << (u ^ ans) << endl;
            return 0;
        }
    }
    return 0;
}
