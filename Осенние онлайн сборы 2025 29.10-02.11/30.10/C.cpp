#include<bits/stdc++.h>

using namespace std;

signed main() {
    freopen("06.txt", "r", stdin);
    freopen("06.out", "w", stdout);
    int r, c;
    cin >> r >> c;
    vector<vector<char>> all(r, vector<char> (c));
    vector<vector<int>> ch(r, vector<int> (c, 1));
    vector<array<int, 3>> allw;
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> all[i][j];
            if (all[i][j] == 'W') {
                allw.push_back({i + j, i, j});
            }
        }
    }
    //sort(allw.begin(), allw.end());
    vector<vector<char>> ans = all;
    for (auto [sum, i, j] : allw) {
        if (j - 1 >= 0 && j + 1 < c) {
            if (all[i][j - 1] != all[i][j + 1] && all[i][j - 1] != 'W' && all[i][j + 1] != 'W' && ch[i][j - 1] && ch[i][j + 1]) {
                ch[i][j + 1] = 0;
                ch[i][j - 1] = 0;
                ans[i][j] = '-';
                continue;
            }
        }
        if (i - 1 >= 0 && i + 1 < r) {
            if (all[i - 1][j] != all[i + 1][j] && all[i - 1][j] != 'W' && all[i + 1][j] != 'W' && ch[i - 1][j] && ch[i + 1][j]) {
                ch[i + 1][j] = 0;
                ch[i - 1][j] = 0;
                ans[i][j] = '|';
                continue;
            }
        }
        if (i - 1 >= 0 && i + 1 < r && j - 1 >= 0 && j + 1 < c) {
            if (all[i + 1][j - 1] != all[i - 1][j + 1] && all[i + 1][j - 1] != 'W' && all[i - 1][j + 1] != 'W' && ch[i + 1][j - 1] && ch[i - 1][j + 1]) {
                ch[i - 1][j + 1] = 0;
                ch[i + 1][j - 1] = 0;
                ans[i][j] = '/';
                continue;
            }
        }
        if (i - 1 >= 0 && i + 1 < r && j - 1 >= 0 && j + 1 < c) {
            if (all[i - 1][j - 1] != all[i + 1][j + 1] && all[i - 1][j - 1] != 'W' && all[i + 1][j + 1] != 'W' && ch[i - 1][j - 1] && ch[i + 1][j + 1]) {
                ch[i + 1][j + 1] = 0;
                ch[i - 1][j - 1] = 0;
                ans[i][j] = (char)(92);
                continue;
            }
        }
    }
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cout << ans[i][j];
        }
        cout << endl;
    }
    return 0;
}
