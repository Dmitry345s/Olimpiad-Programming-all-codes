#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e3 + 2;
int a[MAX][MAX];
int now[MAX][MAX];
int used[MAX][MAX];
int cnt = 0;
vector<pair<int, int>> go = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};

void dfs(int x, int y, int n, int u) {
    if (x < 1 || y < 1 || y > n || x > n || used[x][y]) {
        return;
    }
    used[x][y] = u;
    if (a[x][y] == 1) {
        cnt -= now[x][y];
        if (now[x - 1][y] == 1) {
            now[x][y] = 1;
        }
        cnt += now[x][y];
    }
    if (a[x][y] == 2) {
        cnt -= now[x][y];
        if (now[x][y + 1] == 1) {
            now[x][y] = 1;
        }
        cnt += now[x][y];
    }
    if (a[x][y] == 3) {
        cnt -= now[x][y];
        if (now[x + 1][y] == 1) {
            now[x][y] = 1;
        }
        cnt += now[x][y];
    }
    if (a[x][y] == 4) {
        cnt -= now[x][y];
        if (now[x][y - 1] == 1) {
            now[x][y] = 1;
        }
        cnt += now[x][y];
    }
    if (a[x][y] == 0) {
        for (auto [d1, d2] : go) {
            cnt -= now[x][y];
            if (now[x + d1][y + d2] == 1) {
                now[x][y] = 1;
            }
            cnt += now[x][y];
        }
    }
    if (now[x][y] == 1) {
        for (auto [d1, d2] : go) {
            if (!now[x + d1][y + d2]) {
                dfs(x + d1, y + d2, n, u);
            }
        }
    }
}

signed main() {
    int n, q;
    cin >> n >> q;
    map<char, int> mp;
    mp['U'] = 1;
    mp['R'] = 2;
    mp['D'] = 3;
    mp['L'] = 4;
    vector<pair<int, int>> bc;
    for (int i = 0; i < q; ++i) {
        int r, c;
        char t;
        cin >> r >> c >> t;
        a[r][c] = mp[t];
        bc.push_back({r, c});
    }
    for (int i = 0; i <= n + 1; ++i) {
        for (int j = 0; j <= n + 1; ++j) {
            if (i < 1 || j < 1 || j > n || i > n) {
                now[i][j] = 1;
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (!now[i][j]) {
                dfs(i, j, n, 0);
            }
        }
    }
    vector<int> ans;
    ans.push_back(cnt);
    for (int i = q - 1; i > 0; --i) {
        auto [r, c] = bc[i];
        a[r][c] = 0;
        if (now[r][c] != 1) {
            dfs(r, c, n, 0);
        }
        //cout << cnt << endl;
        ans.push_back(cnt);
    }
    for (int i = q - 1; i >= 0; --i){
        cout << n * n - ans[i] << endl;
    }
    return 0;
}
/*for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= n; ++j) {
        int y = (i - 1) * n + j;
        if (y <= 5 && y != 3 && y != 4) {
            now[i][j] = 1;
        } else {
            now[i][j] = 0;
        }
    }
}
cnt = 3;*/
