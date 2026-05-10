#include<bits/stdc++.h>

using namespace std;

const int INF = 2e9;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> f(n, vector<int> (m));
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
            sum += f[i][j];
        }
    }
    if (n % 2 == 1 && m % 2 == 1 || sum < 0) {
        cout << -1 << endl;
        return 0;
    }
    vector<pair<int, int>> nans;
    if (m % 2 == 0) {
        for (int j = 0; j < m; ++j) {
            nans.push_back({n - 1, j});
        }
        for (int j = m - 1; j >= 0; --j) {
            if (j % 2) {
                for (int i = n - 2; i >= 0; --i) {
                    nans.push_back({i, j});
                }
            } else {
                for (int i = 0; i <= n - 2; ++i) {
                    nans.push_back({i, j});
                }
            }
        }
    } else {
        for (int i = n - 1; i >= 0; --i) {
            nans.push_back({i, 0});
        }
        for (int i = 0; i <= n - 1; ++i) {
            if (i % 2) {
                for (int j = m - 1; j >= 1; --j) {
                    nans.push_back({i, j});
                }
            } else {
                for (int j = 1; j <= m - 1; ++j) {
                    nans.push_back({i, j});
                }
            }
        }
    }
    int in = -1;
    int mn = INF;
    int nsum = 0;
    for (int i = 0; i < n * m; ++i) {
        auto [u, v] = nans[i];
        nsum += f[u][v];
        if (nsum < mn) {
            mn = nsum;
            in = i;
        }
    }
    for (int i = in + 1; i < n * m; ++i) {
        auto [u, v] = nans[i];
        cout << u + 1 << " " << v + 1 << endl;
    }
    for (int i = 0; i <= in; ++i) {
        auto [u, v] = nans[i];
        cout << u + 1 << " " << v + 1 << endl;
    }
    return 0;
}
