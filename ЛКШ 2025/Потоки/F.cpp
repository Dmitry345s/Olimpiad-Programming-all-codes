#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 10000, INF = 1e9;

struct Ed {
    int v, c;
    Ed(int v = 0, int c = 0) : v(v), c(c) {};
};

vector<Ed> ed;
vector<int> g[MAX];

void add(int v, int u, int c) {
    g[v].push_back((int)ed.size());
    ed.push_back(Ed(u, c));
    g[u].push_back((int)ed.size());
    ed.push_back(Ed(v, 0));
}

void upd(int in, int x) {
    ed[in].c -= x;
    ed[(in ^ 1)].c += x;
}

int t;
int used[MAX];

int dfs(int v, int fl, int k) {
    used[v] = 1;
    //cout << v << " " << fl << endl;
    if (v == t) return fl;
    for (int in : g[v]) {
        auto [to, c] = ed[in];
        if (used[to] || c < (1 << k)) continue;
        int x = dfs(to, min(c, fl), k);
        if (x == 0) continue;
        upd(in, x);
        return x;
    }
    return 0;
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> f(n + 1, vector<char> (m + 1));
    array<pair<int, int>, 4> go = {pair<int, int>{-1, 0}, pair<int, int>{1, 0}, pair<int, int>{0, -1}, pair<int, int>{0, 1}};
    int sum = 0;
    int sum2 = 0;
    t = n * m + 1;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> f[i][j];
            int y = (i - 1) * m + j;
            //cout << y << endl;
            if ((i + j + 1) % 2) {
                if (f[i][j] == 'H') {
                    add(0, y, 1);
                    sum += 1;
                }
                if (f[i][j] == 'O') {
                    add(0, y, 2);
                    sum += 2;
                }
                if (f[i][j] == 'N') {
                    add(0, y, 3);
                    sum += 3;
                }
                if (f[i][j] == 'C') {
                    add(0, y, 4);
                    sum += 4;
                }
            } else {
                if (f[i][j] == 'H') {
                    add(y, t, 1);
                    sum2 += 1;
                }
                if (f[i][j] == 'O') {
                    add(y, t, 2);
                    sum2 += 2;
                }
                if (f[i][j] == 'N') {
                    add(y, t, 3);
                    sum2 += 3;
                }
                if (f[i][j] == 'C') {
                    add(y, t, 4);
                    sum2 += 4;
                }
            }
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (f[i][j] == '.' || (i + j) % 2) continue;
            for (auto [x, y] : go) {
                int id = i + x;
                int jd = j + y;
                if (1 <= id && id <= n && 1 <= jd && jd <= m && f[id][jd] != '.') {
                    //cout << i << " " << j << " " << id << " " << jd << endl;
                    add((i - 1) * m + j, (id - 1) * m + jd, 1);
                }
            }
        }
    }
    if (sum == 0) {
        cout << "Invalid" << endl;
        return 0;
    }
    int ans = 0;
    while (true) {
        fill(used, used + MAX, 0);
        int x = dfs(0, INF, 0);
        if (x == 0) break;
        ans += x;
        //cout << ans << endl;
    }
    if (ans == sum2 && ans == sum) {
        cout << "Valid" << endl;
    } else {
        cout << "Invalid" << endl;
    }
    return 0;
}

