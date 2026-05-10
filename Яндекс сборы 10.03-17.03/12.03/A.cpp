#include<bits/stdc++.h>

using namespace std;

int r[2001][3];
int c[2001][3];
int f[2000][2000];

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> f[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            r[i][f[i][j]]++;
            c[j][f[i][j]]++;
        }
    }
    vector<array<int, 3>> ans;
    int rfl = 1;
    while (true) {
        assert((int)ans.size() <= 2 * n);
        int fl = 0;
        for (int i = 0; i < n; ++i) {
            if (r[i][1] == 0 && r[i][2] == 0) {
                r[i][0] = 0;
                continue;
            }
            if (r[i][0] == 0 && r[i][1] == 0) {
                for (int j = 0; j < n; ++j) {
                    if (f[i][j] != -1) {
                        c[j][2]--;
                    }
                    f[i][j] = -1;
                }
                r[i][2] = 0;
                fl = 1;
                ans.push_back({1, i, 2});
                continue;
            }
            if (r[i][0] == 0 && r[i][2] == 0) {
                for (int j = 0; j < n; ++j) {
                    if (f[i][j] != -1) {
                        c[j][1]--;
                    }
                    f[i][j] = -1;
                }
                r[i][1] = 0;
                fl = 1;
                ans.push_back({1, i, 1});
                continue;
            }
        }
        for (int i = 0; i < n; ++i) {
            if (c[i][1] == 0 && c[i][2] == 0) {
                c[i][0] = 0;
                continue;
            }
            if (c[i][0] == 0 && c[i][1] == 0) {
                for (int j = 0; j < n; ++j) {
                    if (f[j][i] != -1) {
                        r[j][2]--;
                    }
                    f[j][i] = -1;
                }
                c[i][2] = 0;
                fl = 1;
                ans.push_back({2, i, 2});
                continue;
            }
            if (c[i][0] == 0 && c[i][2] == 0) {
                for (int j = 0; j < n; ++j) {
                    if (f[j][i] != -1) {
                        r[j][1]--;
                    }
                    f[j][i] = -1;
                }
                c[i][1] = 0;
                fl = 1;
                ans.push_back({2, i, 1});
                continue;
            }
        }
        if (!fl) break;
    }
    for (int i = 0; i < n; ++i) {
        if (c[i][1] + c[i][2] != 0) rfl = 0;
        if (r[i][1] + r[i][2] != 0) rfl = 0;
    }
    reverse(ans.begin(), ans.end());
    if (!rfl) {
        cout << -1 << endl;
    } else {
        cout << (int)ans.size() << endl;
        for (auto [tp, num, c] : ans) {
            cout << tp << " " << num + 1 << " " << c << endl;
        }
    }
    return 0;
}
