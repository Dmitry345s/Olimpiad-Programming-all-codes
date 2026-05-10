#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MOD = 1e9 + 7, MAX = 5e4 + 5;
const int INF = 1e18;

const int K = 230, K2 = 230;
array<int, 7> to_b[K2];
array<int, 2> to_ans[K2];
int af_ps[K2];
int a[MAX + K];
int af_ps_p[MAX + K];

int rget(array<int, 7> now, int a2, int a1, int len) {
    return (now[0] * a2 + now[1] * len + a1 * now[4] + now[6] * len) % MOD;
}

void rbuild(int i) {
    af_ps[i] = (af_ps[i] + rget(to_b[i], to_ans[i][0], to_ans[i][1], K)) % MOD;
    to_ans[i][0] = 0;
    to_ans[i][1] = 0;
    for (int j = K * i; j < K * i + K; ++j) {
        af_ps_p[j] = (af_ps_p[j] + rget(to_b[i], a[j] * a[j] % MOD, a[j], 1)) % MOD;
        a[j] = (a[j] + to_b[i][3]) % MOD;
        to_ans[i][0] = (to_ans[i][0] + a[j] * a[j]) % MOD;
        to_ans[i][1] = (to_ans[i][1] + a[j]) % MOD;
    }
    for (int j = 0; j < 7; ++j) {
        to_b[i][j] = 0;
    }
}

int ans_b(int i) {
    return (af_ps[i] + rget(to_b[i], to_ans[i][0], to_ans[i][1], K)) % MOD;
}

array<int, 7> upd(array<int, 7> a, int x) {
    array<int, 7> ans = {0, 0, 0, 0, 0, 0};
    ans[0] = a[0] + 1;
    ans[2] = (a[2] + x * x) % MOD;
    ans[3] = (a[3] + x) % MOD;
    ans[4] = (a[4] + 2 * a[3] + 2 * x) % MOD;
    ans[5] = (a[5] + 2 * x * a[3]) % MOD;
    ans[1] = (a[1] + a[2] + x * x) % MOD;
    ans[6] = (a[6] + a[5] + 2 * x * a[3]) % MOD;
    return ans;
}

void upd_bl(int i, int x) {
    to_b[i] = upd(to_b[i], x);
}

void update(int l, int r, int x) {
    int nl = l / K;
    int nr = r / K;
    rbuild(nl);
    rbuild(nr);
    if (nl < nr) {
        for (int i = l; i < nl * K + K; ++i) {
            a[i] = (a[i] + x) % MOD;
        }
        for (int i = nr * K; i <= r; ++i) {
            a[i] = (a[i] + x) % MOD;
        }
    } else {
        for (int i = l; i <= r; ++i) {
            a[i] = (a[i] + x) % MOD;
        }
    }
    for (int i = nl * K; i < nl * K + K; ++i) {
        af_ps_p[i] = (af_ps_p[i] + a[i] * a[i]) % MOD;
        af_ps[nl] = (af_ps[nl] + a[i] * a[i]) % MOD;
    }
    if (nl != nr) {
        for (int i = nr * K; i < nr * K + K; ++i) {
            af_ps_p[i] = (af_ps_p[i] + a[i] * a[i]) % MOD;
            af_ps[nr] = (af_ps[nr] + a[i] * a[i]) % MOD;
        }
    }
    rbuild(nl);
    rbuild(nr);
    for (int i = nl + 1; i < nr; ++i) {
        upd_bl(i, x);
    }
    for (int i = 0; i < nl; ++i) {
        upd_bl(i, 0);
    }
    for (int i = nr + 1; i < K2; ++i) {
        upd_bl(i, 0);
    }
}

int get(int l, int r) {
    int nl = l / K;
    int nr = r / K;
    int ans = 0;
    if (nl < nr) {
        for (int i = l; i < nl * K + K; ++i) {
            ans = (ans + rget(to_b[nl], a[i] * a[i] % MOD, a[i], 1) + af_ps_p[i]) % MOD;
        }
        for (int i = nr * K; i <= r; ++i) {
            ans = (ans + rget(to_b[nr], a[i] * a[i] % MOD, a[i], 1) + af_ps_p[i]) % MOD;
        }
    } else {
        for (int i = l; i <= r; ++i) {
            ans = (ans + rget(to_b[nl], a[i] * a[i] % MOD, a[i], 1) + af_ps_p[i]) % MOD;
        }
    }
    for (int i = nl + 1; i < nr; ++i) {
        int u = ans_b(i);
        ans = (ans + u) % MOD;
    }
    return ans;
}

int n, m, q;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        if (a[i] < 0) a[i] += MOD;
        to_ans[i / K][0] = (to_ans[i / K][0] + a[i] * a[i]) % MOD;
        to_ans[i / K][1] = (to_ans[i / K][1] + a[i]) % MOD;
        af_ps_p[i] = a[i] * a[i] % MOD;
    }
    for (int i = 0; i < K2; ++i) {
        af_ps[i] = to_ans[i][0];
    }
    vector<array<int, 5>> all;
    for (int i = 0; i < m; ++i) {
        int l, r, x;
        cin >> l >> r >> x;
        --l; --r;
        if (x < 0) x += MOD;
        all.push_back({i + 1, -1, x, l, r});
    }
    for (int i = 0; i < q; ++i) {
        int l, r, x, y;
        cin >> l >> r >> x >> y;
        --x; --l; --r;
        all.push_back({x, i, -1, l, r});
        all.push_back({y, i, 1, l, r});
    }
    vector<int> ans(q);
    sort(all.begin(), all.end());
    for (int i = 0; i < (int)all.size(); ++i) {
        auto [t, ch, x, l, r] = all[i];
        if (ch == -1) {
            update(l, r, x);
        } else {
            if (t == -1) continue;
            ans[ch] = (ans[ch] + x * get(l, r) + MOD) % MOD;
        }
    }
    for (int i = 0; i < q; ++i) {
        cout << ans[i] << endl;
    }
    return 0;
}
