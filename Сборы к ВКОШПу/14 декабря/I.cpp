#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 4e18;

void gcd(int a, int b, int & x, int & y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return;
    }
    gcd(b, a % b, x, y);
    int u1 = y;
    int u2 = x - (a / b) * y;
    x = u1;
    y = u2;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    int all = 1;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        all *= a[i] / __gcd(a[i], all);
    }
    all *= 2;
    int x = all;
    vector<pair<int, int>> now;
    vector<int> u;
    for (int i = 2; i < all; ++i) {
        if (x == 1) break;
        if (x % i == 0) {
            int cnt = 0;
            int x2 = 1;
            while (x % i == 0) {
                cnt++;
                x /= i;
                x2 *= i;
            }
            now.push_back({i, cnt});
            u.push_back(x2);
        }
    }
    int t = (int)u.size();
    assert(t <= 20);
    int ans = INF;
    for (int i = 0; i < (1 << t); ++i) {
        int p = 1;
        int q = 1;
        for (int j = 0; j < t; ++j) {
            if ((i >> j) & 1) {
                p *= u[j];
            } else {
                q *= u[j];
            }
        }
        int x = 0, y = 0;
        gcd(p, q, x, y);
        //cout << p << " " << q << " " << x << " " << y << endl;
        if (x >= 0) {
            int del = (x + q) / q;
            x -= q * del;
            y += p * del;
        }
        //cout << x << " " << y << endl;
        ans = min(ans, -x * p);
    }
    cout << ans << endl;
    return 0;
}
