#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 1e5 + 1, LN = 27;
int a[MAX];

struct Node {
    int suf[2];
    int pref[2];
    int all;
    int ans;
    Node() {
        suf[0] = 0;
        suf[1] = 0;
        ans = 0;
        pref[0] = 0;
        pref[1] = 0;
        all = 0;
    }
};

Node tree[LN][4 * MAX];

Node mmerge(Node a, Node b) {
    Node c;
    c.ans = a.ans + b.ans + a.suf[0] * b.pref[1] + a.suf[1] * b.pref[0];
    c.suf[0] = b.suf[0] + a.suf[b.all];
    c.suf[1] = b.suf[1] + a.suf[(b.all ^ 1)];
    c.pref[0] = a.pref[0] + b.pref[a.all];
    c.pref[1] = a.pref[1] + b.pref[(a.all ^ 1)];
    c.all = (b.all ^ a.all);
    return c;

}

void build(int v, int l, int r, int in) {
    if (l + 1 == r) {
        tree[in][v] = Node();
        tree[in][v].suf[(a[l] >> in) & 1] = 1;
        tree[in][v].pref[(a[l] >> in) & 1] = 1;
        tree[in][v].ans = ((a[l] >> in) & 1);
        tree[in][v].all = ((a[l] >> in) & 1);
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m, in);
    build(2 * v + 1, m, r, in);
    tree[in][v] = mmerge(tree[in][2 * v], tree[in][2 * v + 1]);
}

void update(int v, int l, int r, int i, int x, int in) {
    if (l + 1 == r) {
        tree[in][v] = Node();
        tree[in][v].suf[(x >> in) & 1] = 1;
        tree[in][v].pref[(x >> in) & 1] = 1;
        tree[in][v].ans = ((x >> in) & 1);
        tree[in][v].all = ((x >> in) & 1);
        return;
    }
    int m = (l + r) / 2;
    if (i < m) {
        update(2 * v, l, m, i, x, in);
    } else {
        update(2 * v + 1, m, r, i, x, in);
    }
    tree[in][v] = mmerge(tree[in][2 * v], tree[in][2 * v + 1]);
}

Node get(int v, int l, int r, int ql, int qr, int in) {
    if (qr <= l || r <= ql) return Node();
    if (ql <= l && r <= qr) return tree[in][v];
    int m = (l + r) / 2;
    return mmerge(get(2 * v, l, m, ql, qr, in), get(2 * v + 1, m, r, ql, qr, in));
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < LN; ++i) {
        build(1, 0, n, i);
    }
    for (int _ = 0; _ < q; ++_) {
        int t;
        cin >> t;
        if (t == 1) {
            int in, x;
            cin >> in >> x;
            --in;
            for (int i = 0; i < LN; ++i) {
                update(1, 0, n, in, x, i);
            }
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            int ans = 0;
            for (int i = 0; i < LN; ++i) {
                ans += (1ll << i) * get(1, 0, n, l, r, i).ans;
            }
            cout << ans << endl;
        }

    }
    return 0;
}
