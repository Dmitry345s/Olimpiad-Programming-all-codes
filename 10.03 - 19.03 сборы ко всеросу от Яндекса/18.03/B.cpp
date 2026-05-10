#include<bits/stdc++.h>

using namespace std;
using ull = unsigned long long;

const int MAX = 2e5 + 1;
int t[MAX];
ull pows[MAX + 1];
ull pref[MAX + 2];
ull tree[4 * MAX];
ull update_tree[4 * MAX];
const ull P = 179;
const ull MOD = 1e9 + 7;

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = ((t[l] + 1) * pows[l]) % MOD;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = (tree[2 * v] + tree[2 * v + 1]) % MOD;
}

void push(int v, int l, int r) {
    if (update_tree[v] == 0) return;
    int x = update_tree[v];
    update_tree[v] = 0;
    update_tree[2 * v] = x;
    update_tree[2 * v + 1] = x;
    int m = (l + r) / 2;
    tree[2 * v] = (x * ((pref[m] - pref[l] + MOD) % MOD)) % MOD;
    tree[2 * v + 1] = (x * ((pref[r] - pref[m] + MOD) % MOD)) % MOD;
}

void update(int v, int l, int r, int ql, int qr, int c) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        tree[v] = (((pref[r] - pref[l] + MOD) % MOD) * c) % MOD;
        update_tree[v] = c;
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r);
    update(2 * v, l, m, ql, qr, c);
    update(2 * v + 1, m, r, ql, qr, c);
    tree[v] = (tree[2 * v] + tree[2 * v + 1]) % MOD;
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        char u;
        cin >> u;
        if (u == 'J') {
            a[i] = 0;
        } else if (u == 'O') {
            a[i] = 1;
        } else {
            a[i] = 2;
        }
    }
    for (int i = 0; i < n; ++i) {
        char u;
        cin >> u;
        if (u == 'J') {
            b[i] = 0;
        } else if (u == 'O') {
            b[i] = 1;
        } else {
            b[i] = 2;
        }
    }
    for (int i = 0; i < n; ++i) {
        char u;
        cin >> u;
        if (u == 'J') {
            c[i] = 0;
        } else if (u == 'O') {
            c[i] = 1;
        } else {
            c[i] = 2;
        }
    }
    vector<vector<int>> def(3, vector<int> (3));
    def[0][0] = 0;
    def[0][1] = 2;
    def[1][0] = 2;
    def[0][2] = 1;
    def[2][0] = 1;
    def[1][1] = 1;
    def[1][2] = 0;
    def[2][1] = 0;
    def[2][2] = 2;
    vector<vector<int>> all;
    vector<vector<int>> st(3);
    st[0] = a;
    st[1] = b;
    st[2] = c;
    sort(st.begin(), st.end());
    do {
        vector<int> now = st[0];
        all.push_back(now);
        for (int i = 1; i < 3; ++i) {
            for (int j = 0; j < n; ++j) {
                now[j] = def[now[j]][st[i][j]];
            }
            all.push_back(now);
        }
    } while (next_permutation(st.begin(), st.end()));
    sort(all.begin(), all.end());
    all.erase(unique(all.begin(), all.end()), all.end());
    vector<ull> all2;
    for (auto s : all) {
        ull h = 0;
        for (int c : s) {
            h *= P;
            h %= MOD;
            h += c + 1;
            h %= MOD;
        }
        all2.push_back(h);
    }
    int q;
    cin >> q;
    for (int i = 0; i < n; ++i) {
        char u;
        cin >> u;
        if (u == 'J') {
            t[i] = 0;
        } else if (u == 'O') {
            t[i] = 1;
        } else {
            t[i] = 2;
        }
    }
    pows[n - 1] = 1;
    for (int i = n - 2; i >= 0; --i) {
        pows[i] = (pows[i + 1] * P) % MOD;
    }
    pref[0] = 0;
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = (pref[i] + pows[i]) % MOD;
    }
    build(1, 0, n);
    int fl = 0;
    for (int j = 0; j < (int)all2.size(); ++j) {
        //cout << all2[j] << " ";
        if (all2[j] == tree[1]) {
            fl = 1;
        }
    }
    if (fl) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    for (int i = 1; i <= q; ++i) {
        int l, r;
        char u;
        cin >> l >> r >> u;
        --l;
        int y;
        if (u == 'J') {
            y = 0;
        } else if (u == 'O') {
            y = 1;
        } else {
            y = 2;
        }
        update(1, 0, n, l, r, y + 1);
        fl = 0;
        for (int j = 0; j < (int)all2.size(); ++j) {
            if (all2[j] == tree[1]) {
                fl = 1;
            }
        }
        if (fl) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
