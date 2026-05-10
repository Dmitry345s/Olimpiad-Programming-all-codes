#include<bits/stdc++.h>

#pragma GCC optimize("O3","unroll-loops")

#define int long long

using namespace std;

const int MAX = 100000;
const int INF = 1e18;
const int C = 500;

int m;
int a[3][MAX];
int b[3][MAX];
int fl = 0;
vector<int> g[16 * MAX];
pair<int, int> ed[C * MAX];
int s = 0;
int t = 16 * MAX - 1;

void add(int v, int to, int x) {
    g[v].push_back(fl);
    g[to].push_back(fl + 1);
    ed[fl] = {to, x};
    ed[fl + 1] = {v, 0};
    fl += 2;
}

void build(int v, int l, int r, int i) {
    if (l + 1 == r) {
        add(v + 4 * m * i, t, b[i][l]);
        return;
    }
    int c = (l + r) / 2;
    build(2 * v, l, c, i);
    build(2 * v + 1, c, r, i);
    add(v + 4 * m * i, 2 * v + 4 * m * i, INF);
    add(v + 4 * m * i, 2 * v + 1 + 4 * m * i, INF);
}

void update(int v, int l, int r, int i, int ql, int qr, int tt) {
    if (qr <= l || r <= ql) return;
    if (ql <= l && r <= qr) {
        add(tt, v + 4 * m * i, INF);
        return;
    }
    int c = (l + r) / 2;
    update(2 * v, l, c, i, ql, qr, tt);
    update(2 * v + 1, c, r, i, ql, qr, tt);
}

const int LN = 31;
int us[16 * MAX];
int timer = 0;

void relax (int in, int x) {
    ed[in].second -= x;
    ed[in ^ 1].second += x;
}

int d[16 * MAX];

void bfs() {
    fill(d, d + t + 1, INF);
    queue<int> q;
    q.push(0);
    d[0] = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int in : g[v]) {
            auto [to, go] = ed[in];
            if (go == 0 || d[v] + 1 >= d[to]) continue;
            d[to] = d[v] + 1;
            q.push(to);
        }
    }
}

int dfs(int v, int k, int fl) {
    if (v == t) return fl;
    us[v] = timer;
    for (int in : g[v]) {
        auto [to, go] = ed[in];
        if (go < (1ll << k) || us[to] == timer || d[to] != d[v] + 1) continue;
        int x = dfs(to, k, min(fl, go));
        if (x > 0) {
            relax(in, x);
            return x;
        }
    }
    return 0;
}

int f_flow() {
    int f = 0;
    while (true) {
        bfs();
        //cout << d[t] << endl;
        if (d[t] == INF) break;
        for (int i = 0; i >= 0; --i) {
            timer++;
            int u = dfs(0, i, INF);
            while (u) {
                f += u;
                timer++;
                u = dfs(0, i, INF);
            }
        }
    }
    return f;
}

int ch(int n, int x) {
    if (n == 0) {
        vector<int> now(m);
        vector<pair<int, int>> all;
        vector<pair<int, int>> all2;
        for (int i = 0; i < m; ++i) {
            now[i] = a[0][i] - b[0][i];
            if (now[i] < 0) {
                all.push_back({now[i], i});
            } else if (now[i] > 0) {
                all2.push_back({now2[i], i});
            }
        }
        for (int i = 0; i < m; ++i) {

        }
        return INF;
    }
    vector<pair<int, int>> now;
    vector<pair<int, int>> now2;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j]) now.push_back({i, j});
            if (b[i][j]) now2.push_back({i, j});
        }
    }
    if ((int)now.size() * (int)now2.size() <= 2500) {
        for (auto [i, j] : now) {
            add(0, i * m + j + 1, a[i][j]);
        }
        for (auto [i, j] : now2) {
            add(i * m + j + n * m + 1, t, b[i][j]);
        }
        for (auto [i, j] : now) {
            for (auto [i2, j2] : now2) {
                int d = abs(i - i2) + abs(j - j2);
                if (d <= x) {
                    add(i * m + j + 1, i2 * m + j2 + 1 + n * m, INF);
                }
            }
        }
    } else {
        for (int i = 0; i < n; ++i) {
            build(1, 0, m, i);
        }
        int to_add = 4 * m * n + 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                int v = i * m + j + to_add;
                add(0, v, a[i][j]);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                for (int go = 0; go < n; ++go) {
                    int l = j - (x - abs(go - i)), r = j + (x - abs(go - i));
                    int tt = i * m + j + to_add;
                    int rl = max(0ll, l), rr = min(r, m - 1) + 1;
                    //cout << i << " " << j << " " << x << " " << go << " " << rl << " " << rr << endl;
                    if (a[i][j] != 0) update(1, 0, m, go, rl, rr, tt);
                }
            }
        }
    }
    int ans = f_flow();
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while(_--) {
        int n;
        cin >> n >> m;
        int sum = 0;
        t = 15 * m + 1;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> a[i][j];
                sum += a[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> b[i][j];
            }
        }
        int l = -1, r = n + m - 2;
        while (l + 1 < r) {
            //cout << l << " " << r << endl;
            for (int i = 0; i < t; ++i) {
                g[i].clear();
            }
            fl = 0;
            int c = (l + r) / 2;
            int u = ch(n, c);
            //cout << u << " " << c << endl;
            if (u < sum) {
                l = c;
            } else {
                r = c;
            }
        }
        cout << r << endl;
    }
    return 0;
}
