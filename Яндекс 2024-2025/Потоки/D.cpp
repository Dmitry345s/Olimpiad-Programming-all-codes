#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int to, cap;
    Edge(int to = 0, int cap = 0) : to(to), cap(cap) {}
};

const int MAX = 25e2 + 2, INF = 1e4;
vector<Edge> all;
vector<int> g[2 * MAX];

int add_edge(int a, int b, int c) {
    Edge sr = Edge(b, c);
    Edge rev = Edge(a, 0);
    int x = (int)all.size();
    all.push_back(sr);
    all.push_back(rev);
    return x;
}

int s, t;
int used[2 * MAX];

int dfs(int v, int flow) {
    used[v] = 1;
    if (v == t) return flow;
    for (int to : g[v]) {
        if (used[all[to].to] || all[to].cap <= 0) continue;
        int x = dfs(all[to].to, min(flow, all[to].cap));
        all[to].cap -= x;
        all[(to ^ 1)].cap += x;
        flow -= x;
        if (x > 0) {
            return x;
        }
    }
    return 0;
}

void get_ans(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[all[to].to] || all[to].cap <= 0) continue;
        get_ans(all[to].to);
    }
}

signed main() {
    int m, n;
    cin >> n >> m;
    int k, l;
    cin >> k >> l;
    vector<vector<int>> f(n, vector<int> (m));
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        f[x][y] = 1;
    }
    vector<vector<int>> f2(n, vector<int> (m, INF));
    for (int i = 0; i < l; ++i) {
        int x, y;
        cin >> x >> y;
        --x; --y;
        f2[x][y] = 1;
    }
    int xa, ya, xb, yb;
    cin >> xa >> ya >> xb >> yb;
    --xa; --ya; --xb; --yb;
    s = xa * m + ya; t = xb * m + yb;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j]) continue;
            int x = add_edge(i * m + j, i * m + j + n * m, f2[i][j]);
            g[i * m + j].push_back(x);
            g[i * m + j + n * m].push_back((x ^ 1));
            for (int d1 = -1; d1 <= 1; ++d1) {
                for (int d2 = -1; d2 <= 1; ++d2) {
                    if (abs(d1) + abs(d2) != 1) continue;
                    int i2 = i + d1, j2 = j + d2;
                    if (i2 < 0 || j2 < 0 || i2 >= n || j2 >= m) continue;
                    if (f[i2][j2]) continue;
                    int x = add_edge(i * m + j + n * m, i2 * m + j2, INF);
                    g[i * m + j + n * m].push_back(x);
                    g[i2 * m + j2].push_back((x ^ 1));
                }
            }
        }
    }
    int ans = 0;
    while (true) {
        fill(used, used + n * m * 2, 0);
        int x = dfs(s, INF);
        if (x == 0) break;
        ans += x;
    }
    if (ans > l) {
        cout << -1 << endl;
        return 0;
    }
    fill(used, used + n * m * 2, 0);
    get_ans(s);
    vector<pair<int, int>> rans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (used[i * m + j] != used[i * m + j + n * m]) {
                rans.push_back({i, j});
            }
        }
    }
    cout << (int)rans.size() << endl;
    for (auto [x, y] : rans) {
        cout << x + 1 << " " << y + 1 << endl;
    }
    return 0;
}
