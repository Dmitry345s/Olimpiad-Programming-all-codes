#include<bits/stdc++.h>

using namespace std;

const int LN = 18;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m;
    cin >> n >> m;
    vector<int> ds(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> ds[i];
    }
    vector<vector<int>> all(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> all[i][j];
        }
    }
    int _;
    cin >> _;
    vector<vector<int>> edg(n, vector<int> (m));
    for (int i = 0; i < n - 1; ++i) {
        vector<int> now(m);
        for (int j = 0; j < m; ++j) {
            int x = all[i][j] + ds[i];
            int u = lower_bound(all[i + 1].begin(), all[i + 1].end(), x) - all[i + 1].begin();
            if (u < j) {
                now[j] = 0;
            } else {
                now[j] = 1;
            }
        }
        int last = m;
        for (int j = m - 1; j >= 0; --j) {
            edg[i][j] = last - 1;
            if (now[j] == 1) {
                last = j;
            }
        }
    }
    vector<vector<vector<int>>> up(n, vector<vector<int>> (m, vector<int> (LN, m)));
    for (int j = 0; j < m; ++j) {
        for (int k = 0; k < LN; ++k) {
            up[n - 1][j][k] = j;
        }
    }
    for (int i = n - 2; i >= 0; --i) {
        for (int j = 0; j < m; ++j) {
            up[i][j][0] = edg[i][j];
            for (int k = 1; k < LN; ++k) {
                up[i][j][k] = up[min(i + (1 << (k - 1)), n - 1)][up[i][j][k - 1]][k - 1];
            }
        }
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v; --w;
        int x = v - u;
        int now = u;
        for (int k = 0; k < LN; ++k) {
            if ((x >> k) & 1) {
                w = up[now][w][k];
                now += (1 << k);
            }
        }
        cout << all[v][w] << '\n';
    }
    return 0;
}
