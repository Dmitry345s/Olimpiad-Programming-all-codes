#include<bits/stdc++.h>

using namespace std;

int cnt(vector<vector<char>> all, int n, int m) {
    int ans = 0;
    vector<pair<int, int>> go = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (all[i][j] != 'I') continue;
            for (auto [dx, dy] : go) {
                int ni = i + dx, nj = j + dy;
                int n2i = i + 2 * dx, n2j = j + 2 * dy;
                if (n2i < 0 || n2i >= n || n2j < 0 || n2j >= m) continue;
                if (all[ni][nj] == '/' && all[n2i][n2j] == 'O') {
                    ans++;
                }
            }
        }
    }
    return ans;
}

signed main() {
    freopen("12.txt", "w", stdout);
    int n = 50, m = 50, k = 4;
    vector<vector<char>> ans(n, vector<char> (m, '/'));
    for (int i = 7; i < n; ++i) {
        int st = 0;
        if (i == 7) st = 17;
        for (int j = st; j < m; ++j) {
            if (i % 2 == 0) {
                if (j % 4 == 0) {
                    ans[i][j] = 'I';
                } else if (j % 4 == 2) {
                    ans[i][j] = 'O';
                }
            } else {
                if (j % 4 == 1) {
                    ans[i][j] = 'I';
                } else if (j % 4 == 3) {
                    ans[i][j] = 'O';
                }
            }
        }
    }
    cout << cnt(ans, n, m) << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}
