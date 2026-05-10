#include<bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")

using namespace std;

const int MAX = 100;
vector<vector<int>> ch(MAX, vector<int> (MAX));
char r1[MAX][MAX];
char r2[MAX][MAX];
int n, m;
map<char, int> mp;

void dfs(int i, int j, int n, int m, int g) {
    vector<int> r = {0, 0, -1, 1};
    vector<int> l = {-1, 1, 0, 0};
    ch[i][j] = 1;
    for (int k = 0; k < 4; ++k) {
        int ni = i + l[k], nj = j + r[k];
        if (0 <= ni && ni < n && 0 <= nj && nj < m) {
            if (l[k] == 0) {
                if (!ch[ni][nj] && ((g >> mp[r1[i][min(j, nj)]]) & 1)) {
                    dfs(ni, nj, n, m, g);
                }
            } else {
                if (!ch[ni][nj] && ((g >> mp[r2[min(i, ni)][j]]) & 1)) {
                    dfs(ni, nj, n, m, g);
                }
            }
        }
    }
}

signed main() {
    cin >> n >> m;
    mp['C'] = 0;
    mp['Z'] = 1;
    mp['P'] = 2;
    mp['N'] = 3;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m - 1; ++j) {
            cin >> r1[i][j];
        }
    }
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> r2[i][j];
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        --a; --b; --c; --d;
        int ans = 10;
        for (int k = 0; k < (1 << 4); ++k) {
            int cnt = 0;
            for (int l = 0; l < 4; ++l) {
                if ((k >> l) & 1) {
                    cnt++;
                }
            }
            for (int j = 0; j < n; ++j) {
                ch[j].assign(m, 0);
            }
            dfs(a, b, n, m, k);
            if (ch[c][d]) {
                ans = min(ans, cnt);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
