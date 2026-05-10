#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 7340033, U = 20, W = 2187, MAX = (1 << 20), REV2 = (MOD + 1) / 2;

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

void dpf(int l, int r, int k, vector<int> & a) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int lr = k / 2, rr = (k / 2 + n / 2) % n;
    int m = (l + r) / 2;
    for (int i = 0; i < m - l; ++i) {
        int x = a[i + l];
        ll y = a[i + m];
        a[i + l] = md(x + pws[lr] * y);
        a[i + m] = md(x + pws[rr] * y);
    }
    dpf(l, m, lr, a);
    dpf(m, r, rr, a);
}

void bpf(int l, int r, int k, vector<int> & a) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int m = (l + r) / 2;
    int lr = k / 2, rr = (k / 2 + n / 2) % n;
    bpf(l, m, lr, a);
    bpf(m, r, rr, a);
    for (int i = 0; i < m - l; ++i) {
        ll x = a[i + l];
        ll y = a[i + m];
        a[i + l] = md((x + y) * REV2);
        a[i + m] = md(1ll * md((x - y) * REV2) * pws[(n - lr) % n]);
    }
}

void sh(int a, vector<int> & b) {
    while ((int)b.size() > a) {
        b.pop_back();
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
    pws[0] = 1;
    for (int i = 1; i < n; ++i) {
        pws[i] = md(1ll * pws[i - 1] * noww);
    }
    dpf(0, n, 0, a);
    dpf(0, n, 0, b);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = md(1ll * a[i] * b[i]);
    }
    bpf(0, n, 0, c);
    sh(st - 1, c);
    return c;
}

signed main() {
    int m, n;
    cin >> m >> n;
    vector<int> p(n + 1);
    for (int i = 0; i < n + 1; ++i) {
        cin >> p[i];
    }
    if (p[0] == 0) {
        cout << "The ears of a dead donkey" << endl;
        return 0;
    }
    int a = 1;
    vector<int> b = {fpow(p[0], MOD - 2)};
    while (a < m) {
        vector<int> now = fft(p, b);
        for (int i = 0; i < (int)now.size(); ++i) {
            now[i] = (MOD - now[i]);
        }
        now[0] = (now[0] + 2) % MOD;
        a *= 2;
        sh(a, now);
        now = fft(now, b);
        sh(a, now);
        b = now;
    }
    for (int i = 0; i < m; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;
    return 0;
}
