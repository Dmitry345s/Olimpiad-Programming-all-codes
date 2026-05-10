#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5, mod = 1e9 + 7;
vector<vector<int>> trees(11, vector<int> (4 * MAX));

void update(int v, int l, int r, int id, int x, int w) {
    if (l + 1 == r) {
        trees[w][v] = x;
        return;
    }
    int m = (l + r) / 2;
    if (id < m) {
        update(2 * v, l, m, id, x, w);
    } else {
        update(2 * v + 1, m, r, id, x, w);
    }
    trees[w][v] = (trees[w][2 * v] + trees[w][2 * v + 1]) % mod;
}

int get(int v, int l, int r, int ql, int qr, int w) {
    if (qr <= l || r <= ql) {
        return 0;
    }
    if (ql <= l && r <= qr) {
        return trees[w][v];
    }
    int m = (l + r) / 2;
    return (get(2 * v, l, m, ql, qr, w) + get(2 * v + 1, m, r, ql, qr, w)) % mod;
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
        --p[i];
        for (int j = 0; j < 10; ++j) {
            int ch = get(1, 0, n, p[i] + 1, n, j);
            if (j == 0) {
                ch = 1;
            }
            update(1, 0, n, p[i], ch, j + 1);
        }
    }
    cout << get(1, 0, n, 0, n, k) << endl;
    return 0;
}
