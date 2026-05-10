#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 998244353, W = 31, U = 23, MAX = 6e5, REV2 = (MOD + 1) / 2;

int fpow(int a, int x) {
    int ans = 1;
    while (x) {
        if (x % 2) {
            ans = (1ll * ans * a) % MOD;
        }
        x /= 2;
        a = (1ll * a * a) % MOD;
    }
    return ans;
}

int w[MAX];

void dpf(vector<int> & a, int l, int r, int k) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int lr = k / 2, rr = (k / 2 + n / 2) % n;
    int m = (l + r) / 2;
    for (int i = 0; i < m - l; ++i) {
        ll x = a[i + l];
        ll y = a[i + m];
        a[i + l] = (x + w[lr] * y) % MOD;
        a[i + m] = (x + w[rr] * y) % MOD;
    }
    dpf(a, l, m, lr);
    dpf(a, m, r, rr);
}

void bpf(vector<int> & a, int l, int r, int k) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int lr = k / 2, rr = (k / 2 + n / 2) % n;
    int m = (l + r) / 2;
    bpf(a, l, m, lr);
    bpf(a, m, r, rr);
    for (int i = 0; i < m - l; ++i) {
        ll x = a[i + l];
        ll y = a[i + m];
        a[i + l] = ((x + y) * REV2) % MOD;
        a[i + m] = ((x - y + MOD) % MOD * REV2) % MOD * w[(n - lr) % n] % MOD;
    }
}

vector<int> fft(vector<int> a, vector<int> b) {
    int ln = 0;
    int st = (int)a.size() + (int)b.size();
    while ((1 << ln) < st) {
        ln++;
    }
    int n = (1 << ln);
    while ((int)a.size() < n) {
        a.push_back(0);
    }
    while ((int)b.size() < n) {
        b.push_back(0);
    }
    ll noww = fpow(W, (1 << (U - ln)));
    w[0] = 1;
    for (int i = 1; i < n; ++i) {
        w[i] = (w[i - 1] * noww) % MOD;
    }
    dpf(a, 0, n, 0);
    dpf(b, 0, n, 0);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = (1ll * a[i] * b[i]) % MOD;
    }
    bpf(c, 0, n, 0);
    c.resize(st - 1);
    return c;
}

vector<int> inv(vector<int> p, int n) {
    vector<int> b = {fpow(p[0], MOD - 2)};
    int a = 1;
    vector<int> pp = {p[0]};
    while (a < n) {
        int u = a;
        a *= 2;
        while ((int)pp.size() < min(a, (int)p.size())) {
            pp.push_back(p[u]);
            u++;
        }
        vector<int> now = fft(pp, b);
        for (int i = 0; i < min((int)now.size(), a); ++i) {
            now[i] = (MOD - now[i]) % MOD;
        }
        now[0] = (now[0] + 2) % MOD;
        now.resize(a);
        b = fft(b, now);
        b.resize(a);
    }
    b.resize(n);
    return b;
}

vector<int> fpow_fft(vector<int> a, int x, int n) {
    vector<int> ans(1, 1);
    while (x) {
        if (x % 2) {
            ans = fft(ans, a);
            ans.resize(n);
        }
        x /= 2;
        a = fft(a, a);
        a.resize(n);
    }
    return ans;
}

signed main() {
    int n;
    cin >> n;
    vector<int> r(n);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
        r[i] = (MOD - r[i]) % MOD;
    }
    r[0] = (r[0] + 1 + MOD) % MOD;
    vector<int> ans = fft(c, inv(r, n));
    ans.resize(n);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}
