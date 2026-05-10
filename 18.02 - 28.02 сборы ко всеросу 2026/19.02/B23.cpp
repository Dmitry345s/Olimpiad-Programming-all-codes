#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

using namespace std;

const int INF = 100000;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
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
    vector<vector<vector<int>>> alldist(k + 1, vector<vector<int>> (n, vector<int> (m, INF)));
    int cnt = 0;
    for (auto [stx, sty] : sp) {
        vector<vector<int>> ndist(n, vector<int> (m, INF));
        ndist[stx][sty] = 0;
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
                if (ndist[nx][ny] == INF) {
                    q.push({nx, ny});
                    ndist[nx][ny] = ndist[vx][vy] + 1;
                }
            }
        }
        alldist[cnt] = ndist;
        cnt++;
    }
    int ans = 0;
    for (auto [x, y] : sp) {
        ans += alldist[0][x][y];
    }
    vector<int> dp((1 << k), INF);
    dp[0] = ans;
    for (int i = 0; i < (1 << k); ++i) {
        //cout << i << endl;
        vector<int> nall;
        for (int u = 0; u < k; ++u) {
            if ((i >> u) & 1) continue;
            nall.push_back(u);
            dp[i + (1 << u)] = min(dp[i + (1 << u)], dp[i] + alldist[0][sp[u + 1].first][sp[u + 1].second]);
        }
        for (int tt = 0; tt < (int)nall.size(); ++tt) {
            for (int tt2 = tt + 1; tt2 < (int)nall.size(); ++tt2) {
                int u = nall[tt];
                int v = nall[tt2];
                dp[i + (1 << u) + (1 << v)] = min(dp[i + (1 << u) + (1 << v)], dp[i] + alldist[u + 1][sp[v + 1].first][sp[v + 1].second]);
            }
        }
    }
    ans = dp[(1 << k) - 1];
    if (ans >= INF) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }
    return 0;
}
