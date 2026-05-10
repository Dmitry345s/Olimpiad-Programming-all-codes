#include<bits/stdc++.h>

#pragma GCC optmize("O3")
#pragma GCC optmize("unroll-loops")

using namespace std;

const int MAX = 2e3;
bitset<MAX> a[MAX], b[MAX], c[MAX], d[MAX];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = 1;
            b[j][i] = 1;
            c[i][j] = 1;
            d[j][i] = 1;
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        char t;
        cin >> t;
        int x, y;
        cin >> x >> y;
        --x; --y;
        if (t == 'd') {
            int it = b[y]._Find_next(x);
            if (it == MAX) {
                cout << -1 << '\n';
            } else {
                cout << it + 1 << " " << y + 1 << '\n';
            }
        } else if (t == 'u') {
            int it = d[y]._Find_next(n - 1 - x);
            if (it == MAX) {
                cout << -1 << '\n';
            } else {
                cout << n - 1 - it + 1 << " " << y + 1 << '\n';
            }
        } else if (t == 'r') {
            int it = a[x]._Find_next(y);
            if (it == MAX) {
                cout << -1 << '\n';
            } else {
                cout << x + 1 << " " << it + 1 << '\n';
            }
        } else if (t == 'l') {
            int it = c[x]._Find_next(m - 1 - y);
            if (it == MAX) {
                cout << -1 << '\n';
            } else {
                cout << x + 1 << " " << m - 1 - it + 1 << '\n';
            }
        } else {
            a[x][y] = 0;
            b[y][x] = 0;
            c[x][m - 1 - y] = 0;
            d[y][n - 1 - x] = 0;
        }
    }
    return 0;
}
