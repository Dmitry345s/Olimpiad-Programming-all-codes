#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e6;

vector<int> cl(MAX, -1);
vector<vector<int>> g(MAX);
int cnt[10];
vector<int> used(MAX, -1);

void dfs(int v, int num) {
    used[v] = num;
    cnt[cl[v]]++;
    for (int to : g[v]) {
        if (used[to] != -1) continue;
        dfs(to, num);
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> f(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            if (c == '.') {
                f[i][j] = -1;
            } else {
                f[i][j] = c - '0';
                cl[i * m + j] = f[i][j];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        int j = 0;
        while (j < m) {
            while (j < m && f[i][j] == -1) {
                j++;
            }
            if (j == m) continue;
            int l = j;
            int r = j;
            while (r < m && f[i][r] != -1) {
                r++;
            }
            //cout << i << " " << l << " " << r << " " << endl;
            for (int u = l; u < r; ++u) {
                g[i * m + u].push_back(i * m + (r - u - 1 + l));
            }
            j = r;
        }
    }
    //cout << endl;
    for (int j = 0; j < m; ++j) {
        int i = 0;
        while (i < n) {
            while (i < n && f[i][j] == -1) {
                i++;
            }
            if (i == n) continue;
            int l = i;
            int r = i;
            while (r < n && f[r][j] != -1) {
                r++;
            }
            for (int u = l; u < r; ++u) {
                g[u * m + j].push_back((r - u - 1 + l) * m + j);
            }
            i = r;
        }
    }
    int num = 0;
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == -1) continue;
            if (used[i * m + j] == -1) {
                for (int u = 0; u < 10; ++u) {
                    cnt[u] = 0;
                }
                dfs(i * m + j, num);
                int in = -1;
                int minm = 1e9;
                for (int mb = 0; mb < 10; ++mb) {
                    int now = 0;
                    for (int u = 0; u < 10; ++u) {
                        now += abs(mb - u) * cnt[u];
                    }
                    if (now < minm) {
                        minm = now;
                        in = mb;
                    }
                }
                ans.push_back(in);
                num++;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == -1) {
                cout << '.';
            } else {
                cout << ans[used[i * m + j]];
            }
        }
        cout << endl;
    }
    return 0;
}
