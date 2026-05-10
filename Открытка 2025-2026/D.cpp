#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    int nh = 0;
    int mnu = 0, mxd = 0;
    string s;
    cin >> s;
    vector<pair<int, int>> all;
    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[i] == 'U') {
            nh--;
            mnu = min(mnu, nh);
        } else if (s[i] == 'D') {
            nh++;
            mxd = max(mxd, nh);
        } else {
            all.push_back({mnu, mxd});
            mxd = nh;
            mnu = nh;
        }
    }
    all.push_back({mnu, mxd});
    vector<vector<char>> f(n, vector<char> (m));
    vector<vector<int>> pref(m, vector<int> (n + 1));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
        }
    }
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            int c = (f[i][j] == '#');
            pref[j][i + 1] = pref[j][i] + c;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int nx = j;
            int fl = 1;
            for (auto [l, r] : all) {
                if (nx >= m) {
                    fl = 0;
                    break;
                }
                if (i + l < 0) {
                    fl = 0;
                    break;
                }
                if (i + r >= n) {
                    fl = 0;
                    break;
                }
                int sum = pref[nx][i + r + 1] - pref[nx][i + l];
                if (sum) {
                    fl = 0;
                    break;
                }
                nx++;
            }
            ans += fl;
        }
    }
    cout << ans << endl;
    return 0;
}
