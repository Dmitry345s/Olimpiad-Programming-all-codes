#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> v(m + 1), v2(m + 1), v3(n + 1), v4(n + 1);
    for (int i = 0; i < k; ++i) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        v[min(x1, x2)].push_back({min(y1, y2), -1});
        v[min(x1, x2)].push_back({max(y1, y2), 1});
        v3[max(y1, y2)].push_back({min(x1, x2), -1});
        v3[max(y1, y2)].push_back({max(x1, x2), 1});
        v2[max(x1, x2)].push_back({min(y1, y2), -1});
        v2[max(x1, x2)].push_back({max(y1, y2), 1});
        v4[min(y1, y2)].push_back({min(x1, x2), -1});
        v4[min(y1, y2)].push_back({max(x1, x2), 1});
    }
    vector<vector<int>> f(n + 1, vector<int> (m + 1)), f2(n + 1, vector<int> (m + 1));
    for (int i = 0; i < m; ++i) {
        sort(v[i].begin(), v[i].end());
        int l = 0, cnt = 0;
        for (int j = 0; j < n; ++j) {
            while (l < v[i].size() && v[i][l].first == j) {
                cnt += v[i][l].second;
                ++l;
            }
            if (cnt == 0) {
                f[j][i] = 1;
            } else {
                f[j][i] = 0;
            }
        }
    }
    for (int i = 1; i < m + 1; ++i) {
        sort(v2[i].begin(), v2[i].end());
        int l = 0, cnt = 0;
        for (int j = 0; j <= n; ++j) {
            while (l < v2[i].size() && v2[i][l].first == j) {
                cnt += v2[i][l].second;
                ++l;
            }
            if (cnt == 0) {
                f2[j][i] = 1;
            } else {
                f2[j][i] = 0;
            }
        }
    }
    cout << f[0][1] << endl;
    for (int i = 0; i < n; ++i) {
        cout << v3[i].size() << endl;
        sort(v3[i].begin(), v3[i].end());
        for (int j = 0; j < v3[i].size(); ++j) {
            cout << v3[i][j].first << " " << v3[i][j].second << endl;
        }
        int l = 0, cnt = 0;
        for (int j = 0; j <= m; ++j) {
            if (cnt == 0) {
                f[i][j] = (1 && f[i][j]);
            } else {
                f[i][j] = (0 && f[i][j]);
            }
            while (l < v3[i].size() && v3[i][l].first == j) {
                cnt += v3[i][l].second;
                ++l;
            }
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        sort(v4[i].begin(), v4[i].end());
        int l = 0, cnt = 0;
        for (int j = 0; j <= m; ++j) {
            while (l < v4[i].size() && v4[i][l].first == j) {
                cnt += v4[i][l].second;
                ++l;
            }
            if (cnt == 0) {
                f2[j][i] = 1;
            } else {
                f2[j][i] = 0;
            }
        }
    }
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            cout << f[i][j] << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            cout << f2[i][j] << " ";
        }
        cout << endl;
    }
    vector<vector<int>> pref(n + 1, vector<int> (m + 1));
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            if (i == 0 || j == 0) {
                pref[i][j] = f2[i][j];
            }
            pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + f2[i][j];
        }
    }
    int ans = 0;
    for (int i = 0; i < n + 1; ++i) {
        for (int j = 0; j < m + 1; ++j) {
            if (f[i][j]) {
                ans += pref[n][m] - pref[i][m] - pref[n][j] + pref[i][j];
            }
        }
    }
    cout << ans << endl;
    return 0;
}
