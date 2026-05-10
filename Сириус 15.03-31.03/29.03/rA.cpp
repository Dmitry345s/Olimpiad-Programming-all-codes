#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> ans;
int n, m;

void rec(int i, int j, vector<vector<char>> & now, vector<vector<char>> & need) {
    if (i > n - 2 || j > m - 2) return;
    if (now[i][j] == 'L' && now[i + 1][j] == 'L' && now[i][j + 1] == 'R' && now[i + 1][j + 1] == 'R') {
        ans.push_back({i, j});
        now[i][j] = 'U';
        now[i][j + 1] = 'U';
        now[i + 1][j] = 'D';
        now[i + 1][j + 1] = 'D';
        return;
    } else if (now[i][j] == 'U' && now[i + 1][j] == 'D' && now[i][j + 1] == 'U' && now[i + 1][j + 1] == 'D') {
        ans.push_back({i, j});
        now[i][j] = 'L';
        now[i][j + 1] = 'R';
        now[i + 1][j] = 'L';
        now[i + 1][j + 1] = 'R';
        return;
    }
    if (now[i][j] == 'L') {
        rec(i + 1, j, now, need);
    } else {
        rec(i, j + 1, now, need);
    }
    if (now[i][j] == 'L' && now[i + 1][j] == 'L' && now[i][j + 1] == 'R' && now[i + 1][j + 1] == 'R') {
        ans.push_back({i, j});
        now[i][j] = 'U';
        now[i][j + 1] = 'U';
        now[i + 1][j] = 'D';
        now[i + 1][j + 1] = 'D';
        return;
    } else if (now[i][j] == 'U' && now[i + 1][j] == 'D' && now[i][j + 1] == 'U' && now[i + 1][j + 1] == 'D') {
        ans.push_back({i, j});
        now[i][j] = 'L';
        now[i][j + 1] = 'R';
        now[i + 1][j] = 'L';
        now[i + 1][j + 1] = 'R';
        return;
    }
}

signed main() {
    cin >> n >> m;
    vector<vector<char>> now(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> now[i][j];
        }
    }
    vector<vector<char>> need(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> need[i][j];
        }
    }
    while (now != need) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (now[i][j] != need[i][j]) {
                    rec(i, j, now, need);
                }
            }
        }
    }
    if (now == need) {
        cout << ans.size() << endl;
        for (int i = 0; i < (int)ans.size(); ++i) {
            cout << ans[i].first + 1 << " " << ans[i].second + 1 << endl;
        }
    } else {
        cout << -1 << endl;
    }
    return 0;
}
