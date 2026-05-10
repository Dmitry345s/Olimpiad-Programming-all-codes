#include<bits/stdc++.h>

using namespace std;
using ll = long long;

const int MOD = 998244353, W = 31, U = 23, MAX = (1 << 22) + 1;

int pr[MAX];

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

void dpf(int l, int r, int k, vector<int> & a) {
    int n = (int)a.size();
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    for (int i = 0; i < m - l; ++i) {
        int x = a[i + l];
        ll y = a[i + m];
        a[i + l] = md(x + pr[k / 2] * y);
        a[i + m] = md(x - pr[k / 2] * y);
    }
    dpf(l, m, k / 2, a);
    dpf(m, r, (k / 2 + n / 2) % n, a);
}

void bpf(int l, int r, int k, vector<int> & a) {
    int n = (int)a.size();
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    bpf(l, m, k / 2, a);
    bpf(m, r, (k / 2 + n / 2) % n, a);
    for (int i = 0; i < m - l; ++i) {
        ll x = a[i + l];
        ll y = a[i + m];
        a[i + l] = md((x + y) * (MOD + 1) / 2);
        a[i + m] = md(1ll * md((x - y) * (MOD + 1) / 2) * pr[(n - k / 2) % n]);
    }
}

vector<int> fft(vector<int> & a, vector<int> & b) {
    int ln = 0;
    int n = (int)a.size(), m = (int)b.size();
    while ((1 << ln) < n + m) {
        ln++;
    }
    while ((int)a.size() < (1 << ln)) {
        a.push_back(0);
    }
    while ((int)b.size() < (1 << ln)) {
        b.push_back(0);
    }
    ll noww = fpow(W, (1 << (U - ln)));
    pr[0] = 1;
    for (int i = 1; i <= (1 << ln); ++i) {
        pr[i] = md(pr[i - 1] * noww);
    }
    dpf(0, (1 << ln), 0, a);
    dpf(0, (1 << ln), 0, b);
    vector<int> c((1 << ln));
    for (int i = 0; i < (1 << ln); ++i) {
        c[i] = md(1ll * a[i] * b[i]);
    }
    bpf(0, (1 << ln), 0, c);
    return c;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<int> b(m);
    for (int i = 0; i < m; ++i) {
        cin >> b[i];
    }
    vector<int> ans = fft(a, b);
    for (int i = 0; i < n + m - 1; ++i) {
        cout << ans[i] << " ";
    }
    cout << endl;
    return 0;
}

