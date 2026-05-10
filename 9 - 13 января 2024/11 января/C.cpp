#include<bits/stdc++.h>

using namespace std;

int MAX = 5e6;
vector<vector<int>> g(MAX);
vector<int> used(MAX);

void get(vector<vector<char>> b, int n, int m) {
    for (int i = 0; i < 5 * n * m; ++i) {
        g[i].clear();
        used[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int now = i * m + j + 1;
            int now2 = j * n + i + 1;
            if (b[i][j] == '.') continue;
            if (b[i][j] == '/') {
                g[now + i].push_back(now2 + n * (m + 1) + j);
                g[now2 + n * (m + 1) + j].push_back(now + i);
                g[now2 + n * (m + 1) + j + 1].push_back(now + i + 1);
                g[now + i + 1].push_back(now2 + n * (m + 1) + j + 1);
            } else {
                g[now + i].push_back(now2 + n * (m + 1) + j + 1);
                g[now2 + n * (m + 1) + j + 1].push_back(now + i);
                g[now2 + n * (m + 1) + j].push_back(now + i + 1);
                g[now + i + 1].push_back(now2 + n * (m + 1) + j);
            }
        }
    }
}

int sz = 0;
void dfs(int v) {
    used[v] = 1;
    sz++;
    for (int to : g[v]) {
        if (!used[to]) {
            //cout << "!" << " " << v << " " << to << endl;
            dfs(to);
        }
    }
}

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<char>> b(n, vector<char>(m));
    vector<vector<char>> c(n, vector<char> (m, '/'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> b[i][j];
            if (b[i][j] == '.') {
                c[i][j] = '.';
            }
        }
    }
    int ans = 0;
    get(b, n, m);
    for (int i = 1; i <= n * m * 5; ++i) {
        if (!used[i]) {
            sz = 0;
            dfs(i);
            if (sz > 1) {
                ans++;
            }
            //cout << i << " " << ans << endl;
        }
    }
    int ans2 = 0;
    get(c, n, m);
    for (int i = 1; i <= n * m * 5; ++i) {
        if (!used[i]) {
            sz = 0;
            dfs(i);
            if (sz > 1) {
                ans2++;
            }
            //cout << i << " " << ans << endl;
        }
    }
    cout << max(ans2, ans - k) << endl;
    return 0;
    //cout << ans << endl;
    if (k <= 1e9) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (b[i][j] == '.') continue;
                if (b[i][j] == '/') {
                    b[i][j] = '\'';
                } else {
                    b[i][j] = '/';
                }
                get(b, n, m);
                int cnt = 0;
                for (int i = 1; i <= n * m * 5; ++i) {
                    if (!used[i]) {
                        sz = 0;
                        dfs(i);
                        if (sz > 1) {
                            cnt++;
                        }
                    }
                }
                ans = min(ans, cnt);
                if (b[i][j] == '/') {
                    b[i][j] = '\'';
                } else {
                    b[i][j] = '/';
                }
            }
        }
    }
    //cout << ans << endl;
    if (k == 1) {
        cout << ans << endl;
        return 0;
    }
    if (k <= 1e9) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (b[i][j] == '.') continue;
                if (b[i][j] == '/') {
                    b[i][j] = '\'';
                } else {
                    b[i][j] = '/';
                }
                for (int l = 0; l < n; ++l) {
                    for (int u = 0; u < m; ++u) {
                        if (b[l][u] == '.') continue;
                        if (b[l][u] == '/') {
                            b[l][u] = '\'';
                        } else {
                            b[l][u] = '/';
                        }
                        get(b, n, m);
                        int cnt = 0;
                        for (int i = 1; i <= n * m * 5; ++i) {
                            if (!used[i]) {
                                sz = 0;
                                dfs(i);
                                if (sz > 1) {
                                    cnt++;
                                }
                            }
                        }
                        ans = min(ans, cnt);
                        if (b[l][u] == '/') {
                            b[l][u] = '\'';
                        } else {
                            b[l][u] = '/';
                        }
                    }
                }
                if (b[i][j] == '/') {
                    b[i][j] = '\'';
                } else {
                    b[i][j] = '/';
                }
            }
        }
    }
    cout << ans << endl;
    return 0;
}
