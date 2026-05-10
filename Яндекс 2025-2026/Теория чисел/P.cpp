#include<bits/stdc++.h>

# define int long long

using namespace std;

int gcd(int a, int b, int & x, int & y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    int k = gcd(b % a, a, x, y);
    swap(x, y);
    x -= y * (b / a);
    return k;
}

int get(int a, int b) {
    int x = 0, y = 0;
    int d = gcd(a, b, x, y);
    //cout << x << " " << y << endl;
    if (x < 0) {
        int cnt = (-x + b - 1) / b;
        x += cnt * b;
        y -= cnt * a;
    } else {
        int cnt = x / b;
        x -= cnt * b;
        y += cnt * a;
    }
    //cout << x << " " << y << endl;
    return x * a;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> k(m);
    for (int i = 0; i < m; ++i) {
        cin >> k[i];
        if (k[i] == 1) {
            cout << n << endl;
            return 0;
        }
    }
    k.push_back(n);
    m++;
    sort(k.begin(), k.end());
    vector<int> nk;
    for (int i = 0; i < m; ++i) {
        int fl = 1;
        for (int v : nk) {
            if (k[i] % v == 0) fl = 0;
        }
        if (fl) nk.push_back(k[i]);
    }
    m = (int)nk.size();
    int ans = 0;
    for (int i = 1; i < (1 << m); ++i) {
        int x = (1 << m) - 1 - i;
        for (int j = x; j > 0; j = (j - 1) & x) {
            int nd1 = 1;
            int fl1 = -1;
            for (int tt = 0; tt < m; ++tt) {
                if ((i >> tt) & 1) {
                    nd1 = (nd1 * nk[tt]) / __gcd(nd1, nk[tt]);
                    fl1 *= -1;
                }
                if (nd1 > n + 1) break;
            }
            if (nd1 > n + 1) continue;
            int nd2 = 1;
            int fl2 = -1;
            for (int tt = 0; tt < m; ++tt) {
                if ((j >> tt) & 1) {
                    nd2 = (nd2 * nk[tt]) / __gcd(nd2, nk[tt]);
                    fl2 *= -1;
                }
                if (nd2 > n + 1) break;
            }
            if (nd2 > n + 1) continue;
            if (__gcd(nd1, nd2) != 1) continue;
            int mn = get(nd1, nd2);
            if (mn > n) {
                ans -= fl1 * fl2;
            }
            ans += fl1 * fl2 * (max(0ll, (n - mn)) / (nd1 * nd2) + 1);
        }
    }
    cout << ans << endl;
    return 0;
}
