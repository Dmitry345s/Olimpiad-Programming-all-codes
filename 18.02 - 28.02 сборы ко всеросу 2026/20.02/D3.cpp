#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> f(n, vector<int> (m));
    vector<pair<int, int>> all;
    for (int i = 0; i < n; ++i) {
        int sumn = 0;
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
            sumn += f[i][j];
        }
        all.push_back({sumn, -i});
    }
    sort(all.rbegin(), all.rend());
    vector<vector<int>> ch(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            ch[-all[i].second][-all[j].second] = 1;
        }
    }
    int rans = n * m;
    for (int mask = 0; mask < (1 << (n * m)); ++mask) {
        vector<vector<int>> tr(n, vector<int> (m));
        int allsum = 0;
        for (int bit = 0; bit < n * m; ++bit) {
            if ((mask >> bit) & 1) {
                tr[bit / m][bit % m] = 1;
                allsum++;
            }
        }
        vector<int> y(n);
        vector<int> u(n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                y[i] += tr[i][j] * f[i][j];
                u[i] += tr[i][j];
            }
        }
        int fl = 1;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (ch[i][j] && !(y[i] >= y[j] + k * m - k * u[j])) fl = 0;
                if (!ch[i][j] && !(y[j] > y[i] + k * m - k * u[i])) fl = 0;
            }
        }
        if (fl) rans = min(rans, allsum);
    }
    cout << rans << endl;
    return 0;
}
