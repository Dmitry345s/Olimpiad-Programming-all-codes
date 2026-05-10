#include<bits/stdc++.h>

//#define int long long

#pragma GCC optimize("O3","unroll-loops")

using namespace std;
using ll = long long;

const int MAX = 5e5 + 10, LN = 19;
int n;

struct Node {
    int cnt;
    int l;
    int r;
    Node() {
        cnt = 1;
        l = -1;
        r = -1;
    }
};

Node ver[LN * MAX];
int now = 0;
int a[MAX];
int tree[4 * MAX];
ll rtree[4 * MAX];
ll upd_tree[4 * MAX];
int wcp[4 * MAX];

void build0(int v, int l, int r) {
    if (l + 1 == r) {
        rtree[v] = a[l];
        return;
    }
    int m = (l + r) / 2;
    build0(2 * v, l, m);
    build0(2 * v + 1, m, r);
    rtree[v] = max(rtree[2 * v], rtree[2 * v + 1]);
}

void push(int v) {
    ll x = upd_tree[v];
    upd_tree[v] = 0;
    upd_tree[2 * v] += x;
    rtree[2 * v] += x;
    upd_tree[2 * v + 1] += x;
    rtree[2 * v + 1] += x;
}

void update0(int v, int l, int r, int ql, int qr, int x) {
    if (r <= ql || qr <= l) return;
    if (ql <= l && r <= qr) {
        rtree[v] += x;
        upd_tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    push(v);
    update0(2 * v, l, m, ql, qr, x);
    update0(2 * v + 1, m, r, ql, qr, x);
    rtree[v] = max(rtree[2 * v], rtree[2 * v + 1]);
}

int getn(int v, int l, int r, ll x) {
    if (rtree[v] < x) return -1;
    if (l + 1 == r) return l;
    int m = (l + r) / 2;
    push(v);
    if (rtree[2 * v + 1] >= x) {
        return getn(2 * v + 1, m, r, x);
    }
    return getn(2 * v, l, m, x);
}

ll gtt(int v, int l, int r, int in) {
    if (l + 1 == r) return rtree[v];
    int m = (l + r) / 2;
    push(v);
    if (in < m) return gtt(2 * v, l, m, in);
    return gtt(2 * v + 1, m, r, in);
}

int gt_cnt(int v) {
    if (v == -1) return 0;
    return ver[v].cnt;
}

void upd(int v) {
    if (v == -1) return;
    ver[v].cnt = gt_cnt(ver[v].l) + gt_cnt(ver[v].r);
}

int sr(int v, int l, int r, int x, int cp) {
    if (v == -1) return -1;
    int m = (l + r) / 2;
    if (x < l) return -1;
    if (l + 1 == r) {
        ver[cp] = ver[v];
        return cp;
    }
    ver[cp] = ver[v];
    if (ver[v].r != -1 && m <= x) {
        ver[cp].r = sr(ver[v].r, m, r, x, cp + 1);
    } else {
        ver[cp].r = -1;
        ver[cp].l = sr(ver[v].l, l, m, x, cp + 1);
    }
    upd(cp);
    return cp;
}

void build(int v, int l, int r, int ln) {
    wcp[v] = now;
    now += ln + 1;
    ln--;
    if (l + 1 == r) {
        ver[wcp[v]] = Node();
        tree[v] = wcp[v];
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, ln);
    build(2 * v + 1, m, r, ln);
    ver[wcp[v]].l = sr(tree[2 * v], l, m, getn(2 * v, l, m, rtree[2 * v + 1]), wcp[v] + 1);
    ver[wcp[v]].r = tree[2 * v + 1];
    upd(wcp[v]);
    tree[v] = wcp[v];
}

void update(int v, int l, int r, int ql, int qr, int x) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) return;
    int m = (l + r) / 2;
    push(v);
    update(2 * v, l, m, ql, qr, x);
    update(2 * v + 1, m, r, ql, qr, x);
    ver[wcp[v]].l = sr(tree[2 * v], l, m, getn(2 * v, l, m, rtree[2 * v + 1]), wcp[v] + 1);
    ver[wcp[v]].r = tree[2 * v + 1];
    upd(wcp[v]);
    tree[v] = wcp[v];
}

vector<array<int, 3>> all;

void get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        all.push_back({v, l, r});
        return;
    }
    int m = (l + r) / 2;
    push(v);
    get(2 * v, l, m, ql, qr);
    get(2 * v + 1, m, r, ql, qr);
}

ll get_k(int v, int l, int r, int k) {
    if (l + 1 == r) return l;
    int m = (l + r) / 2;
    if (gt_cnt(ver[v].l) >= k) {
        return get_k(ver[v].l, l, m, k);
    }
    return get_k(ver[v].r, m, r, k - gt_cnt(ver[v].l));
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    //cout << sizeof(Node) << endl;
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    build0(1, 0, n);
    build(1, 0, n, LN);
    for (int _ = 0; _ < q; ++_) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            update0(1, 0, n, l, r, x);
            update(1, 0, n, l, r, x);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            --l;
            all.clear();
            get(1, 0, n, l, r);
            vector<int> sz((int)all.size());
            ll nmx = rtree[all.back()[0]];
            sz.back() = ver[tree[all.back()[0]]].cnt;
            for (int i = (int)all.size() - 1; i >= 1; --i) {
                int y = sr(tree[all[i - 1][0]], all[i - 1][1], all[i - 1][2], getn(all[i - 1][0], all[i - 1][1], all[i - 1][2], nmx), now);
                sz[i - 1] = gt_cnt(y);
                if (sz[i - 1]) {
                    nmx = rtree[all[i - 1][0]];
                }
            }
            int in = 0;
            while (in < (int)all.size() && k > sz[in]) {
                k -= sz[in];
                in++;
            }
            if (in == (int)all.size()) {
                cout << -1 << endl;
            } else {
                int ch = get_k(tree[all[in][0]], all[in][1], all[in][2], k);
                cout << gtt(1, 0, n, ch) << endl;
            }
        }
    }
    return 0;
}
