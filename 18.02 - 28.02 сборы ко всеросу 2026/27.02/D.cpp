#include<bits/stdc++.h>

#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> f(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            char c;
            cin >> c;
            f[i][j] = c - '0';
        }
    }
    array<int, 8> rans = {0, 0, 0, 0, 0, 0, 0, 0};
    int cntans = 0;
    for (int l = 0; l < m; ++l) {
        vector<vector<pair<int, int>>> all(n);
        for (int r = l; r < m; ++r) {
            for (int u = 0; u < n; ++u) {
                if (f[u][r] == 0) {
                    if (all[u].empty()) {
                        all[u].push_back({r, r});
                    } else {
                        if (all[u].back().second == r - 1) {
                            all[u].back().second = r;
                        } else {
                            all[u].push_back({r, r});
                        }
                    }
                }
            }
            int nl = 0;
            while (nl < n) {
                if ((int)all[nl].size() > 1) {
                    nl++;
                    continue;
                }
                int nr = nl;
                while (nr < n && (int)all[nr].size() == 0) {
                    nr++;
                }
                int up = nr;
                while (nr < n - 1 && (int)all[nr].size() == 1 && (int)all[nr + 1].size() == 1 && all[nr] == all[nr + 1]) {
                    nr++;
                }
                int dw = nr;
                int nx = dw;
                if (nx == nl) nx++;
                if ((int)all[nr].size() <= 1) nr++;
                while (nr < n && (int)all[nr].size() == 0) {
                    nr++;
                }
                int ss = (r - l + 1) * (nr - nl);
                if (ss > cntans) {
                    cntans = ss;
                    if (up < n) rans = {up, all[up][0].first, dw, all[up][0].second, nl, l, nr - 1, r};
                    if (up == n) {
                        rans = {0, 0, 0, 0, nl, l, nr - 1, r};
                        if (l == 0 && nl == 0) {
                            rans[0] = n - 1;
                            rans[2] = n - 1;
                            rans[1] = m - 1;
                            rans[3] = m - 1;
                        }
                    }
                }
                nl = nx;
            }
        }
    }
    cout << rans[0] + 1 << " " << rans[1] + 1 << " " << rans[2] + 1 << " " << rans[3] + 1 << endl;
    cout << rans[4] + 1 << " " << rans[5] + 1 << " " << rans[6] + 1 << " " << rans[7] + 1 << endl;
    cout << cntans << endl;
    return 0;
}
