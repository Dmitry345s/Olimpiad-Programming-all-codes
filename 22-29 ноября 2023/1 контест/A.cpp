#include<bits/stdc++.h>

using namespace std;

pair<int, int> next(int i, int j, int pri, int prj, vector<string> & f, int n, int m) {
    for (int k = -1; k <= 1; ++k) {
        for (int l = -1; l <= 1; ++l) {
            if (l != 0 && k != 0) continue;
            int ni = i + k, nj = j + l;
            if (0 <= ni && ni < n && 0 <= nj && nj < m && f[ni][nj] == '*' && !(ni == pri && nj == prj) && !(ni == i && nj == j)) {
                return {ni, nj};
            }
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<string> f(n);
    for (int i = 0; i < n; ++i) {
        cin >> f[i];
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] != '#') continue;
            for (int k = -1; k <= 1; ++k) {
                for (int l = -1; l <= 1; ++l) {
                    int ni = i + k, nj = j + l;
                    if (0 <= ni && ni < n && 0 <= nj && nj < m && f[ni][nj] != '#') {
                        f[ni][nj] = '*';
                    }
                }
            }
        }
    }
    /*for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << f[i][j];
        }
        cout << endl;
    }*/
    pair<int, int> first = {-1, -1};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == '*') {
                first = {i, j};
                break;
            }
        }
        if (first != pair<int, int>{-1, -1}) {
            break;
        }
    }
    pair<int, int> now = first, last = {-1, -1};
    do {
        cout << now.first + 1 << " " << now.second + 1 << endl;
        pair<int, int> ch = next(now.first, now.second, last.first, last.second, f, n, m);
        last = now;
        now = ch;
    } while(now != first);
    return 0;
}
