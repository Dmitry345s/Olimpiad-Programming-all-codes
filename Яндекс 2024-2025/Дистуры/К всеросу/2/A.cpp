#include<bits/stdc++.h>

//#define int long long
#pragma GCC optimize("O3")

using namespace std;

int n, m;
const int MAX = 1e3, MAXN = 1e6 + 5;
int used[MAX][MAX];
int st[MAXN];
int f[MAX][MAX];
int cnt = 0;

void dfs(int x, int y, int num) {
    used[x][y] =  num;
    st[num]++;
    if (x - 1 >= 0 && !used[x - 1][y] && f[x - 1][y] == f[x][y]) {
        dfs(x - 1, y, num);
    }
    if (y - 1 >= 0 && !used[x][y - 1] && f[x][y - 1] == f[x][y]) {
        dfs(x, y - 1, num);
    }
    if (x + 1 < n && !used[x + 1][y] && f[x + 1][y] == f[x][y]) {
        dfs(x + 1, y, num);
    }
    if (y + 1 < m && !used[x][y + 1] && f[x][y + 1] == f[x][y]) {
        dfs(x, y + 1, num);
    }
}

int p[MAXN], sz[MAXN], used2[MAXN], sz2[MAX];

int root(int v) {
    vector<int> now;
    while (p[v] != v) {
        now.push_back(v);
        v = p[v];
    }
    for (auto x : now) {
        p[x] = v;
    }
    return v;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    //freopen("test.txt", "r", stdin);
    //freopen("ans.txt", "w", stdout);
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    int num = 0;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (!used[i][j]) {
                num++;
                dfs(i, j, num);
                ans = max(ans, st[num]);
            }
        }
    }
    //cout << cnt << endl;
    vector<pair<int, int>> mp;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n && f[i][j] != f[i + 1][j]) {
                pair<int, int> now = {min(f[i][j], f[i + 1][j]), max(f[i][j], f[i + 1][j])};
                mp.push_back(now);
            }
            if (j + 1 < m && f[i][j] != f[i][j + 1]) {
                pair<int, int> now = {min(f[i][j], f[i][j + 1]), max(f[i][j], f[i][j + 1])};
                mp.push_back(now);
            }
        }
    }
    sort(mp.begin(), mp.end());
    mp.erase(unique(mp.begin(), mp.end()), mp.end());
    vector<vector<pair<int, int>>> gr((int)mp.size());
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i + 1 < n && f[i][j] != f[i + 1][j]) {
                pair<int, int> now = {min(f[i][j], f[i + 1][j]), max(f[i][j], f[i + 1][j])};
                int x = lower_bound(mp.begin(), mp.end(), now) - mp.begin();
                gr[x].push_back({min(used[i + 1][j], used[i][j]), max(used[i][j], used[i + 1][j])});
            }
            if (j + 1 < m && f[i][j] != f[i][j + 1]) {
                pair<int, int> now = {min(f[i][j], f[i][j + 1]), max(f[i][j], f[i][j + 1])};
                int x = lower_bound(mp.begin(), mp.end(), now) - mp.begin();
                gr[x].push_back({min(used[i][j], used[i][j + 1]), max(used[i][j], used[i][j + 1])});
            }
        }
    }
    for (auto & val : gr) {
        //sort(val.begin(), val.end());
        //val.erase(unique(val.begin(), val.end()), val.end());
        for (auto [u, v] : val) {
            p[u] = u;
            sz[u] = st[u];
            sz2[u] = 1;
            p[v] = v;
            sz[v] = st[v];
            sz2[v] = 1;
        }
        for (auto [u, v] : val) {
            int rv = root(v), ru = root(u);
            if (rv != ru) {
                if (sz2[ru] < sz2[rv]) {
                    swap(rv, ru);
                }
                p[rv] = ru;
                sz[ru] += sz[rv];
                sz2[ru] += sz2[rv];
                ans = max(ans, sz[ru]);
            }
        }
        //cout << cnt << endl;
    }
    //cout << cnt << endl;
    cout << ans << endl;
    return 0;
}
