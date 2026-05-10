#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main () {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> f(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    vector<vector<char>> fa = f, sa = f;
    for (int _ = 0; _ < (min(n, m) + 1) / 2; ++_) {
        for (int i = _; i < n - _; ++i) {
            if (_ & 1) {
                fa[i][m - 1 - _] = '#';
                fa[i][_] = '#';
            } else {
                sa[i][m - 1 - _] = '#';
                sa[i][_] = '#';
            }
        }
        for (int j = _; j < m - _; ++j) {
            if (_ & 1) {
                fa[n - 1 - _][j] = '#';
                fa[_][j] = '#';
            } else {
                sa[n - 1 - _][j] = '#';
                sa[_][j] = '#';
            }
        }
        int li = _, lj = m - 2 - _;
        if (li < (n - 1) / 2 && lj >= m / 2) {
            if (f[li][lj] == '#') continue;
            if (_ & 1) {
                fa[li][lj] = '.';
                sa[li][lj] = '#';
            } else {
                sa[li][lj] = '.';
                fa[li][lj] = '#';
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << fa[i][j];
        }
        cout << endl;
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << sa[i][j];
        }
        cout << endl;
    }
    return 0;
}
