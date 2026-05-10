#include<bits/stdc++.h>

#define int long long

using namespace std;

bool tr(int n, int m, vector<vector<int>> c, int in) {
    int sum2 = 0;
    vector<int> st(m);
    for (int i = 0; i < m; ++i) {
        sum2 += c[in][i];
        st[i] = c[in][i];
    }
    vector<vector<int>> may(n);
    for (int i = 0; i < n; ++i) {
        int now = c[in][0] + c[i][0];
        int fl = 1;
        for (int j = 1; j < m; ++j) {
            if (abs(st[j] - now) != abs(st[j] - c[i][j]) && abs(st[j] - now) != abs(st[j] + c[i][j])) {
                fl = 0;
            }
        }
        if (fl) {
            may[i].push_back(1);
        }
        now = c[in][0] - c[i][0];
        fl = 1;
        for (int j = 1; j < m; ++j) {
            if (abs(st[j] - now) != abs(st[j] - c[i][j]) && abs(st[j] - now) != abs(st[j] + c[i][j])) {
                fl = 0;
            }
        }
        if (fl) {
            may[i].push_back(-1);
        }
        if (may[i].empty()) return 0;
    }
    int md = abs(n - m);
    vector<vector<int>> bag(n + 1, vector<int> (md));
    vector<vector<int>> p(n + 1, vector<int> (md));
    bag[0][0] = 1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < md; ++j) {
            for (int zn : may[i]) {
                int now = (((j + zn * c[i][0]) % md) + md) % md;
                if (bag[i][j]) {
                    bag[i + 1][now] = 1;
                    p[i + 1][now] = zn;
                }
            }
        }
    }
    int now = ((-sum2) % md + md) % md;
    if (!bag[n][now]) return 0;
    vector<int> zns(n);
    for (int i = n; i > 0; --i) {

    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> c(n, vector<int> (m));
    vector<vector<int>> ct(m, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> c[i][j];
            ct[j][i] = c[i][j];
        }
    }
    int in = -1, jn = -1;
    int mx = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (c[i][j] > mx) {
                in = i;
                jn = j;
                mx = c[i][j];
            }
        }
    }
    int x1 = tr(n, m, c, in);
    if (x1) return 0;
    int x2 = tr(m, n, ct, jn);
    if (x2) return 0;
    return 0;
}
