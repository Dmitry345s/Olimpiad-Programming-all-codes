#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 998244353, W = 31, U = 23, MAX = (1 << 20), REV2 = (MOD + 1) / 2;

int fpow(int a, int x) {
    int ans = 1;
    while (x > 0) {
        if (x % 2) {
            ans = (1ll * ans * a) % MOD;
        }
        x /= 2;
        a = (1ll * a * a) % MOD;
    }
    return ans;
}

int md(ll a) {
    return ((a % MOD) + MOD) % MOD;
}

int pws[MAX];

void sh(vector<int> & a, int c) {
    while ((int)a.size() > c) {
        a.pop_back();
    }
}

void dpf(int l, int r, int k, vector<int> & a) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int lr = k / 2, rr = (k / 2 + n / 2) % n;
    int m = (l + r) / 2;
    for (int i = 0; i < m - l; ++i) {
        int x = a[i + l];
        ll y = a[i + m];
        a[i + l] = md(x + pws[lr] * y);
        a[i + m] = md(x - pws[lr] * y);
    }
    dpf(l, m, lr, a);
    dpf(m, r, rr, a);
}

void bpf(int l, int r, int k, vector<int> & a) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int lr = k / 2, rr = (k / 2 + n / 2) % n;
    int m = (l + r) / 2;
    bpf(l, m, lr, a);
    bpf(m, r, rr, a);
    for (int i = 0; i < m - l; ++i) {
        ll x = a[i + l];
        ll y = a[i + m];
        a[i + l] = md((x + y) * REV2);
        a[i + m] = md(1ll * md((x - y) * REV2) * pws[(n - lr) % n]);
    }
}

vector<int> fft(vector<int> a, vector<int> b) {
    int ln = 1;
    int st = (int)a.size() + b.size();
    while ((1 << ln) < st) {
        ln++;
    }
    int n = (1 << ln);
    while((int)a.size() < n) {
        a.push_back(0);
    }
    while ((int)b.size() < n) {
        b.push_back(0);
    }
    ll noww = fpow(W, (1 << (U - ln)));
    pws[0] = 1;
    for (int i = 1; i < n; ++i) {
        pws[i] = md(pws[i - 1] * noww);
    }
    dpf(0, n, 0, a);
    dpf(0, n, 0, b);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = md(1ll * a[i] * b[i]);
    }
    bpf(0, n, 0, c);
    sh(c, st - 1);
    return c;
}

vector<int> inv(int x, vector<int> p) {
    vector<int> b = {fpow(p[0], MOD - 2)};
    int a = 1;
    while (a < x) {
        vector<int> pp = p;
        a *= 2;
        sh(pp, a);
        vector<int> now = fft(pp, b);
        sh(now, a);
        for (int i = 0; i < (int)now.size(); ++i) {
            now[i] = (MOD - now[i]) % MOD;
        }
        now[0] = (now[0] + 2) % MOD;
        now = fft(now, b);
        sh(now, a);
        b = now;
    }
    sh(b, x);
    return b;
}

int rev[MAX];

vector<int> ln(vector<int> & a) {
    int n = (int)a.size();
    vector<int> ap(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        ap[i] = (1ll * a[i + 1] * (i + 1)) % MOD;
    }
    vector<int> lnap = fft(ap, inv(2 * n, a));
    vector<int> lna(2 * n);
    for (int i = 1; i < 2 * n; ++i) {
        lna[i] = (1ll * lnap[i - 1] * rev[i]) % MOD;
    }
    return lna;
}

signed main() {
    for (int i = 1; i < (1 << 17); ++i) {
        rev[i] = fpow(i, MOD - 2);
    }
    int n;
    cin >> n;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    vector<int> b = {1};
    int a = 1;
    vector<int> now;
    while (a < n) {
        a *= 2;
        now = ln(b);
        for (int i = 0; i < min(n, a); ++i) {
            now[i] = (p[i] - now[i] + MOD) % MOD;
        }
        now[0] = (now[0] + 1) % MOD;
        b = fft(b, now);
        sh(b, a);
    }
    for (int i = 0; i < n; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;
    return 0;
}

