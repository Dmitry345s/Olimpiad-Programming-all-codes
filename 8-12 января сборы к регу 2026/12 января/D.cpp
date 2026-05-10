#include<bits/stdc++.h>

#pragma GCC optmize ("O3","unroll-loops")

#define int long long

using namespace std;

const int MOD = 232792560;

const int MAX = (1 << 20) + 100;
int tree[4 * MAX];
int upd_tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = 0;
        upd_tree[v] = 1;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
    upd_tree[v] = 1;
}

void push(int v) {
    int x = upd_tree[v];
    upd_tree[v] = 1;
    tree[2 * v] = (tree[2 * v] * x) % MOD;
    tree[2 * v + 1] = (tree[2 * v + 1] * x) % MOD;
    upd_tree[2 * v] = (upd_tree[2 * v] * x) % MOD;
    upd_tree[2 * v + 1] = (upd_tree[2 * v + 1] * x) % MOD;
}

void update(int v, int l, int r, int in) {
    if (l + 1 == r) {
        tree[v] = (tree[v] + 1) % MOD;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    if (in < m) {
        update(2 * v, l, m, in);
    } else {
        update(2 * v + 1, m, r, in);
    }
    tree[v] = (tree[2 * v] + tree[2 * v + 1]) % MOD;
}

int get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return 0;
    if (ql <= l && r <= qr) return tree[v];
    int m = (l + r) / 2;
    push(v);
    return (get(2 * v, l, m, ql, qr) + get(2 * v + 1, m, r, ql, qr)) % MOD;
}

signed main() {
    /*for (int i = 2; i <= 20; ++i) {
        cout << (1 << 20) % i << " ";
    }
    cout << endl;*/
    //cout << (1 << 20) - 1 << endl;
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    vector<pair<char, int>> all(q);
    for (int i = 0; i < q; ++i) {
        cin >> all[i].first >> all[i].second;
    }
    vector<int> ans(q, -1);
    vector<int> rd(q, -1);
    build(1, 0, MAX);
    int add = 0;
    int k = 0;
    vector<int> suf(n + 1);
    for (int i = n - 1; i >= 0; --i) {
        suf[i] = (suf[i + 1] * (1 << 20) + a[i]) % MOD;
    }
    vector<vector<pair<int, int>>> qs(n + 1);
    vector<int> ks(q);
    vector<pair<int, int>> qs2;
    vector<pair<int, int>> to_ans(q, {-1, -1});
    for (int i = 0; i < q; ++i) {
        if (all[i].first == '+') {
            add = (add + all[i].second) % (1 << 20);
        } else if (all[i].first == '<') {
            k = (k + all[i].second) % n;
        } else {
            rd[i] = all[i].second;
            qs[k].push_back({add, i});
            qs2.push_back({add, i});
            ks[i] = k;
        }
    }
    int nsum = 0;
    for (int i = n - 1; i >= 0; --i) {
        upd_tree[1] = (upd_tree[1] * (1 << 20)) % MOD;
        tree[1] = (tree[1] * (1 << 20)) % MOD;
        update(1, 0, MAX, a[i]);
        nsum = (nsum * (1 << 20) + 1) % MOD;
        for (auto [x, in] : qs[i]) {
            int y = (get(1, 0, MAX, (1 << 20) - x, MAX) * (1 << 20)) % MOD;
            to_ans[in].second = (((nsum * x + suf[i] - y) % MOD + MOD) % MOD);
        }
    }
    for (auto [x, in] : qs2) {
        int y = (get(1, 0, MAX, (1 << 20) - x, MAX) * (1 << 20)) % MOD;
        to_ans[in].first = (((nsum * x + suf[0] - y) % MOD + MOD) % MOD);
    }
    vector<int> pows(n + 1);
    pows[0] = 1;
    for (int i = 0; i < n; ++i) {
        pows[i + 1] = (pows[i] * (1 << 20)) % MOD;
    }
    for (int i = 0; i < q; ++i) {
        auto [ans1, ans2] = to_ans[i];
        if (ans1 == -1 && ans2 == -1) continue;
        int prefans = ((ans1 - ans2 * pows[ks[i]]) % MOD + MOD) % MOD;
        ans[i] = (ans2 + prefans * pows[n - ks[i]]) % MOD;
    }
    for (int i = 0; i < q; ++i) {
        if (ans[i] != -1) {
            cout << ans[i] % rd[i] << '\n';
        }
    }
    return 0;
}
/*
int ans1 = suf[0];
int ans2 = suf[k];
int prefans = ((ans1 - ans2 * fpow((1 << 20) % MOD, k, MOD)) % MOD + MOD) % MOD;
ans[i] = (ans2 + prefans * fpow((1 << 20) % MOD, n - k, MOD)) % MOD;
*/
