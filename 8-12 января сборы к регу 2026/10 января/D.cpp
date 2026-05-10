#include<bits/stdc++.h>

//#pragma GCC optimize("O3,unroll-loops")

#define int long long

using namespace std;

const int MAX = 1e5 + 5;
const int C = 8;

struct Node {
    int a[C];
    Node(int x = -1, int in = -1) {
        for (int i = 0; i < C; ++i) {
            a[i] = MAX;
        }
        if (x != -1) {
            a[x] = in;
        }
    }
};

array<int, C> don(int x = -1, int in = -1) {
    array<int, C> a;
    for (int i = 0; i < C; ++i) {
        a[i] = MAX;
    }
    if (x != -1) {
        a[x] = in;
    }
    return a;
}

array<int, C> operator + (array<int, C> a, array<int, C> b) {
    array<int, C> ans;
    for (int i = 0; i < C; ++i) {
        ans[i] = min(a[i], b[i]);
    }
    return ans;
}

int a[MAX];
int n;
array<int, C> tree[4 * MAX];
int upd_tree[4 * MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v] = don(a[l], l);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

void relax(array<int, C> & a, int x) {
    if (x == 0) return;
    if (x == 1) {
        swap(a[0], a[1]);
        swap(a[2], a[3]);
        swap(a[4], a[5]);
        swap(a[6], a[7]);
    } else if (x == 2) {
        swap(a[0], a[2]);
        swap(a[1], a[3]);
        swap(a[4], a[6]);
        swap(a[5], a[7]);
    } else if (x == 3) {
        swap(a[0], a[3]);
        swap(a[1], a[2]);
        swap(a[4], a[7]);
        swap(a[5], a[6]);
    } else {
        for (int i = 0; i < C / 2; ++i) {
            swap(a[i], a[i ^ x]);
        }
    }
}

void push(int v) {
    int x = upd_tree[v];
    upd_tree[v] = 0;
    relax(tree[2 * v], x);
    upd_tree[2 * v] ^= x;
    relax(tree[2 * v + 1], x);
    upd_tree[2 * v + 1] ^= x;
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        relax(tree[v], x);
        upd_tree[v] ^= x;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    tree[v] = tree[2 * v] + tree[2 * v + 1];
}

int get(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return MAX;
    if (tree[v][x] == MAX) return MAX;
    if (ql <= l && r <= qr) return tree[v][x];
    int m = (l + r) / 2;
    push(v);
    return min(get(2 * v, l, m, ql, qr, x), get(2 * v + 1, m, r, ql, qr, x));
}

map<pair<int, int>, int> mp;

int get_len(int l, int r, int x) {
    if (l == r) return mp[{l, x}] = 0;
    int u = get(1, 0, n, l, r, x);
    if (u == MAX) return mp[{l, x}] = 0;
    if (mp.find({l, x}) != mp.end()) return mp[{l, x}];
    int ans = 0;
    for (int i = x + 1; i < C; ++i) {
        ans = max(ans, get_len(u + 1, r, i));
    }
    return mp[{l, x}] = ans + 1;
}

int get_ans(int l, int r) {
    vector<vector<int>> to_ans(8, vector<int> (8, MAX));
    vector<int> mn(8, MAX);
    int ans = 0;
    for (int i = 0; i < 8; ++i) {
        to_ans[i][0] = get(1, 0, n, l, r, i);
        for (int j = 1; j <= i; ++j) {
            if (mn[j - 1] == MAX) continue;
            to_ans[i][j] = get(1, 0, n, mn[j - 1], r, i);
        }
        for (int j = 0; j <= i; ++j) {
            mn[j] = min(mn[j], to_ans[i][j]);
        }
    }
    for (int j = 0; j < 8; ++j) {
        if (mn[j] < MAX) {
            ans = max(ans, j);
        }
    }
    return ans + 1;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0);
    cout.tie(0);
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build(1, 0, n);
    for (int i = 0; i < q; ++i) {
        string t;
        cin >> t;
        if (t == "xor") {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            update(1, 0, n, l, r, x);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            cout << get_ans(l, r) << '\n';
        }
    }
    return 0;
}
