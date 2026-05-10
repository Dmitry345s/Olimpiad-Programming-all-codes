#include<bits/stdc++.h>

using namespace std;

mt19937 rnd(time(0));

int ch (vector<vector<int>> & f, int n, int m) {
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            for (int l = i + 1; l < n; ++l) {
                for (int k = j + 1; k < m; ++k) {
                    if (f[i][j] == f[l][k] && f[i][k] == f[i][j] && f[i][j] == f[l][j]) {
                        /*int rnd1 = rnd() % 2;
                        int rnd2 = rnd() % 2;
                        int x = rnd1 * i + (1 ^ rnd1) * l;
                        int y = rnd2 * j + (1 ^ rnd2) * k;
                        int st = f[x][y];
                        while (st == f[x][y]) {
                            f[x][y] = rnd() % 3 + 1;
                        }*/
                        cnt++;
                    }
                }
            }
        }
    }
    return cnt;
}

pair<int, vector<vector<int>>> solve(vector<vector<int>> f, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == 3) {
                f[i][j] = 2;
            }
        }
    }
    int k = ch(f, n, m);
    int cnt = 1;
    int MAX = 1e4;
    while (cnt < MAX && k != 0) {
        int x = rnd() % n;
        int y = rnd() % m;
        vector<vector<int>> new_f = f;
        new_f[x][y] = rnd() % 2 + 1;
        int p = ch(new_f, n, m);
        if (p < k || (double)rand() / (double)(RAND_MAX + 1) < pow((double)(MAX) / (double) (cnt * cnt * (p - k) * (p - k)), 5)) {
            f = new_f;
            k = p;
        }
        cnt++;
    }
    return {k, f};
}

signed main() {
    int cnt2 = 0;
    vector<vector<int>> to_ans(10, vector<int> (10));
    to_ans = {{2, 2, 3, 1, 1, 3, 1, 2, 3, 3},
            {1, 3, 1, 2, 1, 2, 3, 2, 3, 2},
            {2, 1, 2, 2, 1, 3, 3, 3, 1, 1},
            {3, 3, 1, 1, 3, 3, 2, 2, 2, 1},
            {2, 1, 1, 3, 3, 1, 2, 3, 3, 2},
            {1, 1, 2, 1, 3, 2, 3, 1, 2, 3},
            {2, 3, 1, 3, 2, 2, 1, 1, 1, 3},
            {1, 3, 3, 2, 2, 1, 1, 3, 2, 1},
            {3, 2, 2, 1, 2, 1, 2, 3, 1, 3},
            {3, 2, 3, 3, 1, 1, 3, 1, 2, 2}};
    int n, m, c;
    cin >> n >> m >> c;
    if (c == 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << to_ans[i][j] << " ";
            }
            cout << endl;
        }
    } else {
        auto [k, to_ans2] = solve(to_ans, n, m);
        //cout << ch(to_ans2) << endl;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << to_ans2[i][j] << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
