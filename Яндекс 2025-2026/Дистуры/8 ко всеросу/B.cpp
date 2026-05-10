#include<bits/stdc++.h>

#pragma GCC optimize("Ofast")

using namespace std;

int good(int x, int y, int n, int m) {
    return (0 <= x && x < n) && (0 <= y && y < m);
}

int in (int x, int y, int xl, int yl, int xr, int yr) {
    if (x == xl && (y == yl || y == yr) || x == xr && (y == yl || y == yr)) return 0;
    return (xl <= x && x <= xr) && (yl <= y && y <= yr);
}

vector<vector<int>> p;

int root(int i, int v) {
    if (p[i][v] == v) return v;
    return p[i][v] = root(i, p[i][v]);
}

const int K = 80;

const int MAX = 4e6 + 1;
int c;

int tree[MAX];

void add(int i, int x) {
    for (; i < c + 5; i = (i | (i + 1))) {
        tree[i] += x;
    }
}

int sum(int i) {
    int ans = 0;
    for (; i >= 0; i = (i & (i + 1)) - 1) {
        ans += tree[i];
    }
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int r, n;
    cin >> r >> c >> n;
    int fl = 0;
    if (c > r) {
        fl = 1;
        swap(r, c);
    }
    p.resize(r);
    for (int i = 0; i < r; ++i) {
        p[i].resize(c + 1);
        for (int j = 0; j < c + 1; ++j) {
            p[i][j] = j;
        }
    }
    if (fl) swap(r, c);
    int xs, ys;
    int xe, ye;
    cin >> xs >> ys >> xe >> ye;
    --xs; --ys; --xe; --ye;
    vector<vector<char>> f(r, vector<char> (c));
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            cin >> f[i][j];
        }
    }
    if (fl) {
        swap(xs, ys);
        swap(xe, ye);
        vector<vector<char>> rf(c, vector<char> (r));
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                rf[j][i] = f[i][j];
            }
        }
        f = rf;
        swap(r, c);
    }
    if (n <= K) {
        deque<pair<int, int>> q;
        vector<vector<int>> dist(r, vector<int> (c, r * c + 1));
        dist[xs][ys] = 0;
        q.push_back({xs, ys});
        p[xs][ys] = ys + 1;
        vector<pair<int, int>> go = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
        int cnt = 0;
        while (!q.empty()) {
            cnt++;
            //if (cnt > 10) break;
            auto [x, y] = q.front();
            if (x == xe && y == ye) break;
            q.pop_front();
            for (auto [dx, dy] : go) {
                int xt = x + dx, yt = y + dy;
                if (!good(xt, yt, r, c)) continue;
                if (f[xt][yt] == '.' && dist[xt][yt] > dist[x][y]) {
                    dist[xt][yt] = dist[x][y];
                    q.push_front({xt, yt});
                    p[xt][yt] = yt + 1;
                }
            }
            //cout << x << " " << y << endl;
            for (int i = 0; i < 2 * n + 1; ++i) {
                int ri = min(max(x - n + i, 0), r - 1);
                int stj = max(y - n, 0);
                stj = root(ri, stj);
                while (stj <= min(y + n, c - 1)) {
                    //cout << "& " << ri << " " << stj << endl;
                    if (in(ri, stj, x - n, y - n, x + n, y + n)) {
                        dist[ri][stj] = dist[x][y] + 1;
                        q.push_back({ri, stj});
                        p[ri][stj] = stj + 1;
                    }
                    stj = root(ri, stj + 1);
                }
            }
        }
        cout << dist[xe][ye] << endl;
    } else {
        vector<pair<int, int>> ntp;
        ntp.push_back({xs, ys});
        vector<vector<int>> dist(r, vector<int> (c, r * c + 1));
        dist[xs][ys] = 0;
        int cnt = 0;
        while (dist[xe][ye] == r * c + 1) {
            //cout << cnt << endl;
            cnt++;
            deque<pair<int, int>> q;
            for (auto v : ntp) {
                q.push_back(v);
            }
            ntp.clear();
            vector<pair<int, int>> go = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
            int u;
            vector<pair<int, int>> now;
            int fl = 0;
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop_front();
                if (x == xe && y == ye) {
                    fl = 1;
                    break;
                }
                now.push_back({x, y});
                u = dist[x][y];
                for (auto [dx, dy] : go) {
                    int xt = x + dx, yt = y + dy;
                    if (!good(xt, yt, r, c)) continue;
                    if (f[xt][yt] == '.' && dist[xt][yt] > dist[x][y]) {
                        dist[xt][yt] = dist[x][y];
                        q.push_back({xt, yt});
                    }
                }
            }
            if (fl) break;
            vector<vector<pair<int, int>>> all(r + 1);
            for (auto [x, y] : now) {
                int op1 = max(0, x - n);
                int l1 = max(y - n + 1, 0);
                int r1 = min(y + n, c);
                int en1 = min(x + n + 1, r);

                int op2 = max(0, x - n + 1);
                int l2 = max(0, y - n);
                int r2 = min(c, y + n + 1);
                int en2 = min(r, x + n);

                all[op1].push_back({l1, 1});
                all[op1].push_back({r1, -1});
                all[en1].push_back({l1, -1});
                all[en1].push_back({r1, 1});

                all[op2].push_back({l2, 1});
                all[op2].push_back({r2, -1});
                all[en2].push_back({l2, -1});
                all[en2].push_back({r2, 1});
            }
            for (int i = 0; i < r + 1; ++i) {
                for (auto [in, x] : all[i]) {
                    add(in, x);
                }
                if (i < r) {
                    for (int j = 0; j < c; ++j) {
                        if (dist[i][j] < u + 1) continue;
                        int y = sum(j);
                        if (y == 0) continue;
                        ntp.push_back({i, j});
                        dist[i][j] = u + 1;
                    }
                }
            }
        }
        cout << dist[xe][ye] << endl;
    }
    return 0;
}
