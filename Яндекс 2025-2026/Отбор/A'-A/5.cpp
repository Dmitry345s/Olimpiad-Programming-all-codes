#include<bits/stdc++.h>

using namespace std;

const int MAX = 3e5 + 1, INF = 1e9;

void update(int v, int l, int r, int in, int x, vector<int> & tree) {
    if (l + 1 == r) {
        tree[v] = max(tree[v], x);
        return;
    }
    int m = (l + r) / 2;
    if (in < m) {
        update(2 * v, l, m, in, x, tree);
    } else {
        update(2 * v + 1, m, r, in, x, tree);
    }
    tree[v] = max(tree[2 * v], tree[2 * v + 1]);
}

int get(int v, int l, int r, int ql, int qr, vector<int> & tree) {
    if (r <= ql || qr <= l) return 0;
    if (ql <= l && r <= qr) return tree[v];
    int m = (l + r) / 2;
    return max(get(2 * v, l, m, ql, qr, tree), get(2 * v + 1, m, r, ql, qr, tree));
}

signed main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    if (n == 1) {
        cout << 0 << endl;
        return 0;
    }
    string s;
    cin >> s;
    vector<int> treeu(4 * n, 0), treed(4 * n, 0);
    for (int i = 0; i < n; ++i) {
        int mxu = get(1, 0, n, 0, a[i], treeu);
        int mxd = get(1, 0, n, a[i] + 1, n, treed);
        //cout << mxu << " " << mxd << endl;
        if (s[mxu] == 'U') {
            update(1, 0, n, a[i], mxu + 1, treeu);
        } else {
            update(1, 0, n, a[i], mxu + 1, treed);
        }
        if (s[mxd] == 'U') {
            update(1, 0, n, a[i], mxd + 1, treeu);
        } else {
            update(1, 0, n, a[i], mxd + 1, treed);
        }

    }
    cout << max(treeu[1], treed[1]) - 1 << endl;
    return 0;
}
