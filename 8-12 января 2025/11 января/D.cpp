#include<bits/stdc++.h>
#pragma GCC optimize("unroll-loops","O3")

#define int long long

using namespace std;

const int MAX = 1e5 + 1;
int a[MAX], d[MAX];

struct Line {
    int k, b;
    Line(int k = 0, int b = 0) : k(k), b(b) {}
    int get(int x) {
        return k * x + b;
    }
};

struct Node {
    int vl, vr;
    Line u;
    Node(Line u2) {
        u = u2;
        vl = -1;
        vr = -1;
    }
};

const long long INF = 2e18, INF0 = 2e9 + 1;
vector<Node> tree[4 * MAX];
Line MAXM = Line(0, INF);

void add(Line a, int l, int r, int v, int t) {
    int m = (l + r) / 2;
    int u = a.get(m);
    int u2 = tree[t][v].u.get(m);
    if (u < u2) {
        swap(a, tree[t][v].u);
    }
    if (l + 1 == r) return;
    if (a.get(l) < tree[t][v].u.get(l)) {
        if (tree[t][v].vl == -1) {
            tree[t][v].vl = (int)tree[t].size();
            tree[t].push_back(Node(a));
        } else {
            add(a, l, m, tree[t][v].vl, t);
        }
    } else {
        if (tree[t][v].vr == -1) {
            tree[t][v].vr = (int)tree[t].size();
            tree[t].push_back(Node(a));
        } else {
            add(a, m, r, tree[t][v].vr, t);
        }
    }
}

int get(int v, int l, int r, int in, int t) {
    if (l + 1 == r) return tree[t][v].u.get(in);
    int m = (l + r) / 2;
    int ans = 0;
    if (in < m) {
        if (tree[t][v].vl == -1) {
            ans = INF;
        } else {
            ans = get(tree[t][v].vl, l, m, in, t);
        }
    } else {
        if (tree[t][v].vr == -1) {
            ans = INF;
        } else {
            ans = get(tree[t][v].vr, m, r, in, t);
        }
    }
    return min(ans, tree[t][v].u.get(in));
}

void build(int v, int l, int r) {
    tree[v].push_back(Node(Line(0, INF)));
    for (int i = l; i < r; ++i) {
        add(Line(d[i], a[i]), 0, INF0, 0, v);
    }
    if (l + 1 == r) return;
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
}

int getr(int v, int l, int r, int k, int ql, int qr) {
    if (qr <= l || r <= ql) return INF;
    if (ql <= l && r <= qr) return get(0, 0, INF0, k, v);
    int m = (l + r) / 2;
    return min(getr(2 * v, l, m, k, ql, qr), getr(2 * v + 1, m, r, k, ql, qr));
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> a[i] >> d[i];
    }
    build(1, 0, n);
    int q;
    cin >> q;
    int l, r, k;
    for (int i = 0; i < q; ++i) {
        cin >> l >> r >> k;
        --l; k--;
        cout << getr(1, 0, n, k, l, r) << endl;
    }
    return 0;
}
