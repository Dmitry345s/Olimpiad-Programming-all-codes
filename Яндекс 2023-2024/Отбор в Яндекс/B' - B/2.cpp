#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n, vector<int> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
        }
    }
    vector<vector<int>> ans;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (i == n - 1 && j == m - 1) {
                continue;
            }
            if (a[i][j] & 1) {
                if (j == m - 1) {
                    ans.push_back({i, j, i + 1, j});
                    a[i + 1][j] += 1;
                } else {
                    ans.push_back({i, j, i, j + 1});
                    a[i][j + 1] += 1;
                }
            }
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i][0] + 1 << " " << ans[i][1] + 1 << " " << ans[i][2] + 1 << " " << ans[i][3] + 1 << endl;
    }
    return 0;
}

