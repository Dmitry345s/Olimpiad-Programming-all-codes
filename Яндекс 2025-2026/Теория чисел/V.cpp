#include<bits/stdc++.h>

# define int long long

#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")

using namespace std;

int fpow(int a, int x, int mod) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (1ll * ans * a) % mod;
        }
        a = (1ll * a * a) % mod;
        x /= 2;
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int a, p;
        cin >> p >> a;
        if (p == 2) {
            cout << a << endl;
            continue;
        }
        if (a == 0) {
            cout << 0 << endl;
            continue;
        }
        if (fpow(a, (p - 1) / 2, p) == p - 1) {
            cout << -1 << endl;
            continue;
        }
        int z = 2;
        while (fpow(z, (p - 1) / 2, p) == 1) {
            z++;
        }
        int q = p - 1;
        int s = 0;
        while (q % 2 == 0) {
            q /= 2;
            s++;
        }
        int r = fpow(a, (q + 1) / 2, p);
        int t = fpow(a, q, p);
        int m = s;
        int c = fpow(z, q, p);
        while (t != 1) {
            int u = t;
            int i = 1;
            for (; i < m; ++i) {
                u = (u * u) % p;
                if (u == 1) break;
            }
            int b = fpow(c, fpow(2, m - i - 1, p), p);
            int b2 = (b * b) % p;
            m = i;
            t = (t * b2) % p;
            r = (r * b) % p;
            c = b2;
            //cout << t << " " << r << " " << c << " " << m << endl;
        }
        cout << r << endl;
    }
    return 0;
}
