#include<bits/stdc++.h>

//#define int long long

using namespace std;

int ch(vector<vector<char>> all) {
    int k = (int)all.size();
    if (k == 1) {
        if (all[0][0] == '1') return 1;
        return 0;
    }
    vector<int> tr(k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            if (all[i][j] == '1') {
                tr[i] = 1;
                vector<char> nall;
                for (int u = 0; u < k; ++u) {
                    for (int w = 0; w < k; ++w) {
                        if (u != i && w != j) {
                            nall.push_back(all[u][w]);
                        }
                    }
                }
                vector<vector<char>> rall(k - 1, vector<char> (k - 1));
                for (int uu = 0; uu < (k - 1) * (k - 1); ++uu) {
                    rall[uu / (k - 1)][uu % (k - 1)] = nall[uu];
                }
                if (!ch(rall)) return 0;
            }
        }
    }
    for (int i = 0; i < k; ++i) {
        if (!tr[i]) {
            return 0;
        }
    }
    return 1;
}

signed main() {
    int n;
    cin >> n;
    vector<vector<char>> f(n, vector<char> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> f[i][j];
        }
    }
    int ans = n * n;
    for (int i = 0; i < (1 << (n * n)); ++i) {
        int nans = 0;
        vector<vector<char>> nf = f;
        for (int j = 0; j < n * n; ++j) {
            int x = j / n;
            int y = j % n;
            int c = ((i >> j) & 1);
            if (c) {
                nf[x][y] = '1';
                nans++;
            }
        }
        if (ch(nf)) {
            ans = min(ans, nans);
        }
    }
    cout << ans << endl;
    return 0;
}
