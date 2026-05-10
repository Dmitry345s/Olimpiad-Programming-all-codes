#include<bits/stdc++.h>

#define int long long

using namespace std;

void push(int v, int l, int r, vector<int> & tree, vector<int> & update_tree) {
    int x = update_tree[v];
    update_tree[v] = 0;
    update_tree[2 * v] += x;
    update_tree[2 * v + 1] += x;
    int m = (l + r) / 2;
    tree[2 * v] += x;
    tree[2 * v + 1] += x;
}

void update1(int v, int l, int r, int ql, int qr, int x, vector<int> & tree, vector<int> & update_tree) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        update_tree[v] += x;
        tree[v] += x;
        return;
    }
    int m = (l + r) / 2;
    push(v, l, r, tree, update_tree);
    update1(2 * v, l, m, ql, qr, x, tree, update_tree);
    update1(2 * v + 1, m, r, ql, qr, x, tree, update_tree);
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

void update2(int v, int l, int r, int in, int x, vector<int> & tree, vector<int> & update_tree) {
    if (l + 1 == r) {
        tree[v] = x;
        return;
    }
    push(v, l, r, tree, update_tree);
    int m = (l + r) / 2;
    if (in < m) {
        update2(2 * v, l, m, in, x, tree, update_tree);
    } else {
        update2(2 * v + 1, m, r, in, x, tree, update_tree);
    }
    tree[v] = min(tree[2 * v], tree[2 * v + 1]);
}

const int INF = 1e18;

int get(int v, int l, int r, int ql, int qr, vector<int> & tree, vector<int> & update_tree) {
    if (qr <= l || r <= ql) return INF;
    if (ql <= l && r <= qr) {
        return tree[v];
    }
    int m = (l + r) / 2;
    push(v, l, r, tree, update_tree);
    return min(get(2 * v, l, m, ql, qr, tree, update_tree), get(2 * v + 1, m, r, ql, qr, tree, update_tree));
}

signed main() {
    int _;
    cin >> _;
    while (_--) {
        int n, q, x, y;
        cin >> n >> q >> x >> y;
        x--;
        y--;
        vector<int> dp1m(4 * n), updp1m(4 * n);
        vector<int> dp1p(4 * n), updp1p(4 * n);
        vector<int> dp2m(4 * n), updp2m(4 * n);
        vector<int> dp2p(4 * n), updp2p(4 * n);
        for (int i = 0; i < n; ++i) {
            update2(1, 0, n, i, INF, dp2m, updp2m);
            update2(1, 0, n, i, INF, dp2p, updp2p);
            update2(1, 0, n, i, INF, dp1m, updp1m);
            update2(1, 0, n, i, INF, dp1p, updp1p);
        }
        update2(1, 0, n, x, -x, dp2m, updp2m);
        update2(1, 0, n, x, x, dp2p, updp2p);
        update2(1, 0, n, y, -y, dp1m, updp1m);
        update2(1, 0, n, y, y, dp1p, updp1p);
        vector<int> pos1, pos2;
        pos1.push_back(x);
        pos2.push_back(y);
        for (int i = 1; i <= q; ++i) {
            int t;
            cin >> t;
            t--;
            int u = abs(t - pos2[i - 1]);
            int u2 = abs(t - pos1[i - 1]);
            int u3 = min(get(1, 0, n, 0, t, dp1m, updp1m) + t, get(1, 0, n, t, n, dp1p, updp1p) - t);
            int u4 = min(get(1, 0, n, 0, t, dp2m, updp2m) + t, get(1, 0, n, t, n, dp2p, updp2p) - t);
            update1(1, 0, n, 0, n, u, dp2p, updp2p);
            update1(1, 0, n, 0, n, u, dp2m, updp2m);
            update1(1, 0, n, 0, n, u2, dp1p, updp1p);
            update1(1, 0, n, 0, n, u2, dp1m, updp1m);
            int p1 = pos1[i - 1];
            int u5 = min(u3, get(1, 0, n, p1, p1 + 1, dp2m, updp2m) + p1);
            //cout << u5 << endl;
            update2(1, 0, n, p1, u5 - p1, dp2m, updp2m);
            update2(1, 0, n, p1, u5 + p1, dp2p, updp2p);
            int p2 = pos2[i - 1];
            int u6 = min(u4, get(1, 0, n, p2, p2 + 1, dp1m, updp1m) + p2);
            //cout << u6 << endl;
            update2(1, 0, n, p2, u6 - p2, dp1m, updp1m);
            update2(1, 0, n, p2, u6 + p2, dp1p, updp1p);
            pos1.push_back(t);
            pos2.push_back(t);
        }
        int ans = INF;
        for (int i = 0; i < n; ++i) {
            ans = min(ans, min(get(1, 0, n, i, i + 1, dp1m, updp1m), get(1, 0, n, i, i + 1, dp2m, updp2m)) + i);
        }
        cout << ans << endl;
    }
    return 0;
}
