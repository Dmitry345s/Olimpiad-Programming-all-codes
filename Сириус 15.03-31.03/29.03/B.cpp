#include<bits/stdc++.h>

using namespace std;

const int MAX = 151;
char f[MAX][MAX];
vector<vector<int>> used(MAX, vector<int> (MAX, 0));

void dfs2(int x, int y, int & n, int & m) {
    used[x][y] = 1;
    if (x + 1 < n && !used[x + 1][y] && f[x + 1][y] == '.') {
        dfs2(x + 1, y, n, m);
    }
    if (y + 1 < m && !used[x][y + 1] && f[x][y + 1] == '.') {
        dfs2(x, y + 1, n, m);
    }
}

void dfs3(int x, int y, int n, int m) {
    used[x][y] = 1;
    if (x - 1 >= 0 && !used[x - 1][y] && f[x - 1][y] == '.') {
        dfs3(x - 1, y, n, m);
    }
    if (y - 1 >= 0 && !used[x][y - 1] && f[x][y - 1] == '.') {
        dfs3(x, y - 1, n, m);
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cout.tie(0);
    cin.tie(0);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    int cnt = 0;
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int a, b, c;
        cin >> a;
        vector<pair<int, int>> sts(a);
        for (int j = 0; j < a; ++j) {
            cin >> sts[j].first >> sts[j].second;
            sts[j].first--;
            sts[j].second--;
        }
        cin >> b;
        vector<pair<int, int>> bls(b);
        for (int j = 0; j < b; ++j) {
            cin >> bls[j].first >> bls[j].second;
            bls[j].first--;
            bls[j].second--;
        }
        cin >> c;
        vector<pair<int, int>> fns(c);
        for (int j = 0; j < c; ++j) {
            cin >> fns[j].first >> fns[j].second;
            fns[j].first--;
            fns[j].second--;
        }
        int ans = 0;
        if (a * b < b * c) {
            for (int j = 0; j < b; ++j) {
                f[bls[j].first][bls[j].second] = '#';
                for (int l = 0; l < a; ++l) {
                    used.assign(n, vector<int> (m, 0));
                    dfs2(sts[l].first, sts[l].second, n, m);
                    for (int k = 0; k < c; ++k) {
                        if (used[fns[k].first][fns[k].second]) {
                            ans++;
                        }
                    }
                }
                f[bls[j].first][bls[j].second] = '.';
            }
        } else {
            for (int j = 0; j < b; ++j) {
                f[bls[j].first][bls[j].second] = '#';
                for (int l = 0; l < c; ++l) {
                    used.assign(n, vector<int> (m, 0));
                    dfs3(fns[l].first, fns[l].second, n, m);
                    for (int k = 0; k < a; ++k) {
                        if (used[sts[k].first][sts[k].second]) {
                            ans++;
                        }
                    }
                }
                f[bls[j].first][bls[j].second] = '.';
            }
        }
        cnt += min(a * b, b * c) * n * m;
        cout << ans << '\n';
    }
}
