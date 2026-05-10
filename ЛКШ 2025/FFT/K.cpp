#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 998244353, W = 31, U = 23, MAX = (1 << 18), REV2 = (MOD + 1) / 2;

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

int w[MAX];

void dpf(int l, int r, int k, vector<int> & a) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int m = (l + r) / 2;
    int lr = k / 2, rr = (k / 2 + n / 2) % n;
    for (int i = 0; i < m - l; ++i) {
        ll x = a[i + l];
        ll y = a[i + m];
        a[i + l] = md(x + w[lr] * y);
        a[i + m] = md(x - w[lr] * y);
    }
    dpf(l, m, lr, a);
    dpf(m, r, rr, a);
}

void bpf(int l, int r, int k, vector<int> & a) {
    if (l + 1 == r) return;
    int n = (int)a.size();
    int m = (l + r) / 2;
    int lr = k / 2, rr = (k / 2 + n / 2)  % n;
    bpf(l, m, lr, a);
    bpf(m, r, rr, a);
    for (int i = 0; i < m - l; ++i) {
        ll x = a[i + l];
        ll y = a[i + m];
        a[i + l] = ((x + y) * REV2) % MOD;
        a[i + m] = (1ll * w[(n - lr) % n] * md((x - y) * REV2)) % MOD;
    }
}

void sh(vector<int> & a, int c) {
    while ((int)a.size() > c) {
        a.pop_back();
    }
}

vector<int> fft(vector<int> a, vector<int> b) {
    int st = (int)a.size() + (int)b.size();
    int ln = 0;
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
    dpf(0, n, 0, a);
    dpf(0, n, 0, b);
    vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        c[i] = (1ll * a[i] * b[i]) % MOD;
    }
    bpf(0, n, 0, c);
    sh(c, st - 1);
    return c;
}

signed main() {
    int m;
    cin >> m;
    string a, b;
    cin >> a >> b;
    reverse(a.begin(), a.end());
    array<char, 4> now = {'A', 'C', 'G', 'T'};
    vector<int> ans(2 * m - 1);
    for (char c : now) {
        vector<int> na(m);
        vector<int> nb(m);
        for (int i = 0; i < m; ++i) {
            if (a[i] == c) {
                na[i] = 1;
            }
            if (b[i] == c) {
                nb[i] = 1;
            }
        }
        vector<int> ch = fft(na, nb);
        for (int i = 0; i < 2 * m - 1; ++i) {
            ans[i] = (ans[i] + ch[i]) % MOD;
        }
    }
    for (int i = m; i < 2 * m - 1; ++i) {
        ans[i - m] += ans[i];
    }
    int in = -1;
    int mx = -1;
    for (int i = 0; i < m; ++i) {
        if (ans[i] > mx) {
            in = i;
            mx = ans[i];
        }
    }
    cout << mx << " " << (m - 1 - in) << endl;
    return 0;
}
