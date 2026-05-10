#include<bits/stdc++.h>

#define int long long

using namespace std;
using ld = long double;
using d = double;

const int INF = 100000;

mt19937 rnd(228);

d rd() {
    int a = rnd() % (1ll << 30);
    return (d)a / (d)(1ll << 30);
}

const int MAX = 100;
int f[MAX][MAX];
const d C = 0.999;

int solve(int k) {
    int rans = INF;
    int cnt = 2000;
    int nans = 0;
    vector<int> go(k);
    for (int i = 0; i < k; i += 2) {
        go[i] = i + 1;
        go[i + 1] = i;
        nans += f[i][i + 1];
    }
    while (cnt > 0) {
        rans = min(rans, nans);
        if (k == 2) return rans;
        d T = 1;
        int cnt2 = 15000;
        while (cnt2 > 0) {
            T *= C;
            int y1 = rnd() % k;
            int y2 = rnd() % k;
            cnt2--;
            if (y1 == y2 || y1 == go[y2]) continue;
            int trans = nans - f[y1][go[y1]] - f[y2][go[y2]] + f[y1][go[y2]] + f[y2][go[y1]];
            if (trans < nans || exp((nans - trans) / T) - rd() > 0) {
                nans = trans;
                swap(go[y1], go[y2]);
                go[go[y1]] = y1;
                go[go[y2]] = y2;
            }
            rans = min(rans, nans);
        }
        //cout << T << endl;
        cnt--;
    }
    return rans;
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<char>> all(n, vector<char> (m));
    int is, js;
    vector<pair<int, int>> sp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> all[i][j];
            if (all[i][j] == 'S') {
                sp.push_back({i, j});
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (all[i][j] == 'X') {
                sp.push_back({i, j});
            }
        }
    }
    int alldist[k + 1][n][m];
    for (int i = 0; i < k + 1; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int u = 0; u < m; ++u) {
                alldist[i][j][u] = INF;
            }
        }
    }
    int cnt = 0;
    for (auto [stx, sty] : sp) {
        alldist[cnt][stx][sty] = 0;
        queue<pair<int, int>> q;
        q.push({stx, sty});
        vector<pair<int, int>> go = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        while (!q.empty()) {
            auto [vx, vy] = q.front();
            q.pop();
            for (auto [dx, dy] : go) {
                int nx = vx + dx;
                int ny = vy + dy;
                if (nx < 0 || nx >= n || ny < 0 || ny >= m || all[nx][ny] == '#') continue;
                if (alldist[cnt][nx][ny] == INF) {
                    q.push({nx, ny});
                    alldist[cnt][nx][ny] = alldist[cnt][vx][vy] + 1;
                }
            }
        }
        cnt++;
    }
    int ans = 0;
    for (auto [x, y] : sp) {
        ans += alldist[0][x][y];
    }
    if (k % 2 == 0) {
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                f[i][j] = alldist[i + 1][sp[j + 1].first][sp[j + 1].second];
                if (f[i][j] == INF) {
                    cout << -1 << endl;
                    return 0;
                }
            }
        }
        ans += solve(k);
    } else {
        for (int i = 0; i < k + 1; ++i) {
            for (int j = 0; j < k + 1; ++j) {
                f[i][j] = alldist[i][sp[j].first][sp[j].second];
                if (f[i][j] == INF) {
                    cout << -1 << endl;
                    return 0;
                }
            }
        }
        ans += solve(k + 1);
    }
    cout << ans << endl;
    return 0;
}
