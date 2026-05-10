#include<bits/stdc++.h>

using namespace std;

vector<pair<int, int>> ans;

int get(int cnt, vector<vector<char>> & now, vector<vector<char>> & need, int n, int m) {
    int ch = 0;
    for (int i = cnt; i < n - cnt - 1; ++i) {
        int j = m - cnt - 2;
        if (now[i + 1][j + 1] != need[i + 1][j + 1]) {
            if (now[i][j] == 'L' && now[i + 1][j] == 'L' && now[i][j + 1] == 'R' && now[i + 1][j + 1] == 'R') {
                ans.push_back({i, j});
                ch++;
                now[i][j] = 'U';
                now[i][j + 1] = 'U';
                now[i + 1][j] = 'D';
                now[i + 1][j + 1] = 'D';
            } else if (now[i][j] == 'U' && now[i + 1][j] == 'D' && now[i][j + 1] == 'U' && now[i + 1][j + 1] == 'D') {
                ans.push_back({i, j});
                ch++;
                now[i][j] = 'L';
                now[i][j + 1] = 'R';
                now[i + 1][j] = 'L';
                now[i + 1][j + 1] = 'R';
            }
        }
        j = cnt;
        if (i != n - cnt - 2) {
            if (now[i][j] != need[i][j]) {
                if (now[i][j] == 'L' && now[i + 1][j] == 'L' && now[i][j + 1] == 'R' && now[i + 1][j + 1] == 'R') {
                    ans.push_back({i, j});
                    ch++;
                    now[i][j] = 'U';
                    now[i][j + 1] = 'U';
                    now[i + 1][j] = 'D';
                    now[i + 1][j + 1] = 'D';
                } else if (now[i][j] == 'U' && now[i + 1][j] == 'D' && now[i][j + 1] == 'U' && now[i + 1][j + 1] == 'D') {
                    ans.push_back({i, j});
                    ch++;
                    now[i][j] = 'L';
                    now[i][j + 1] = 'R';
                    now[i + 1][j] = 'L';
                    now[i + 1][j + 1] = 'R';
                }
            }
        }
    }
    for (int j = cnt; j < m - cnt - 1; ++j) {
        int i = cnt;
        if (j != m - cnt - 2) {
            if (now[i][j] != need[i][j]) {
                if (now[i][j] == 'L' && now[i + 1][j] == 'L' && now[i][j + 1] == 'R' && now[i + 1][j + 1] == 'R') {
                    ans.push_back({i, j});
                    ch++;
                    now[i][j] = 'U';
                    now[i][j + 1] = 'U';
                    now[i + 1][j] = 'D';
                    now[i + 1][j + 1] = 'D';
                } else if (now[i][j] == 'U' && now[i + 1][j] == 'D' && now[i][j + 1] == 'U' && now[i + 1][j + 1] == 'D') {
                    ans.push_back({i, j});
                    ch++;
                    now[i][j] = 'L';
                    now[i][j + 1] = 'R';
                    now[i + 1][j] = 'L';
                    now[i + 1][j + 1] = 'R';
                }
            }
        }
        i = n - cnt - 2;
        if (now[i + 1][j + 1] != need[i + 1][j + 1]) {
            if (now[i][j] == 'L' && now[i + 1][j] == 'L' && now[i][j + 1] == 'R' && now[i + 1][j + 1] == 'R') {
                ans.push_back({i, j});
                ch++;
                now[i][j] = 'U';
                now[i][j + 1] = 'U';
                now[i + 1][j] = 'D';
                now[i + 1][j + 1] = 'D';
            } else if (now[i][j] == 'U' && now[i + 1][j] == 'D' && now[i][j + 1] == 'U' && now[i + 1][j + 1] == 'D') {
                ans.push_back({i, j});
                ch++;
                now[i][j] = 'L';
                now[i][j + 1] = 'R';
                now[i + 1][j] = 'L';
                now[i + 1][j + 1] = 'R';
            }
        }
    }
    return ch;
}

signed main() {
    int n, m;
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
    int cnt = 0;
    vector<vector<int>> used(n, vector<int> (m));
    int num = 0;
    while (now != need && cnt < 5000) {
        cnt++;
        int k = get(num, now, need, n, m);
        if (k == 0) {
            num++;
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
