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
    return 0;
}
