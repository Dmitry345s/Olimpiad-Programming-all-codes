#include<bits/stdc++.h>
#pragma GCC optimize("O3","unroll-loops")
//#pragma GCC optimize("Ofast")

using namespace std;

int vim = 0;

array<long long, 3> mmerge(array<long long, 3> a, array<long long, 3> b) {
    a[0] += b[0];
    a[1] = min(a[1], b[1]) + 1;
    a[2] = -1;
    return a;
}

const int MAX = (1 << 20);
array<long long, 3> tree[2 * MAX + 3];
int a[MAX];

void build(int v, int l, int r) {
    if (l + 1 == r) {
        tree[v][0] = a[l];
        tree[v][1] = 0;
        tree[v][2] = -1;
        return;
    }
    int m = (l + r) / 2;
    build(2 * v, l, m);
    build(2 * v + 1, m, r);
    tree[v] = mmerge(tree[2 * v], tree[2 * v + 1]);
}

void push(int v) {
    if (tree[v][2] == -1) return;
    tree[2 * v][2] = tree[v][2];
    tree[2 * v + 1][2] = tree[v][2];
    tree[2 * v][0] = tree[v][2] * (1 << tree[2 * v][1]);
    tree[2 * v + 1][0] = tree[v][2] * (1 << tree[2 * v + 1][1]);
    tree[v][2] = -1;
}

void update(int v, int l, int r, int ql, int qr, int d) {
    if (qr <= l || r <= ql) {
        return;
    }
    if (ql <= l && r <= qr) {
        //cout << l << " " << r << " " << tree[v].ans << endl;
        tree[v][2] = d;
        tree[v][0] = 1ll * d * (1 << tree[v][1]);
        return;
    }
    push(v);
    int m = (l + r) / 2;
    int u = (vim >> (tree[v][1] - 1)) & 1;
    update(2 * v + u, l, m, ql, qr, d);
    update(2 * v + (u ^ 1), m, r, ql, qr, d);
    tree[v] = mmerge(tree[2 * v], tree[2 * v + 1]);
}

long long get(int v, int l, int r, int ql, int qr) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        //cout << l << " " << r << " " << tree[v].ju[0] << endl;
        return tree[v][0];
    }
    push(v);
    int m = (l + r) / 2;
    int u = (vim >> (tree[v][1] - 1)) & 1;
    //cout << "! " << l << " " << r << " " << u << endl;
    return get(2 * v + u, l, m, ql, qr) + get(2 * v + (u ^ 1), m, r, ql, qr);
}

/*void all(int v, int l, int r) {
    cout << l  << " " << r << " ";
    cout << tree[v].ans << " " << tree[v].p1 << " " << tree[v].p2 << " " << tree[v].h << endl;
    if (l + 1 == r) return;
    push(v);
    int m = (l + r) / 2;
    all(2 * v, l, m);
    all(2 * v + 1, m, r);
}*/

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int sz = (1 << n);
    for (int i = 0; i < sz; ++i) {
        cin >> a[i];
    }
    build(1, 0, sz);
    int m;
    cin >> m;
    vector<long long> ans;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r, k, v;
            cin >> l >> r >> k >> v;
            //++r;
            vim = (vim ^ k);
            update(1, 0, sz, l, r + 1, v);
            vim = (vim ^ k);
            //all(1, 0, sz);
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            //++r;
            vim = (vim ^ k);
            ans.push_back(get(1, 0, sz, l, r + 1));
            vim = (vim ^ k);
        }
    }
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] << '\n';
    }
    return 0;
}
