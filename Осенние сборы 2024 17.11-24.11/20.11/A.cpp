#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m, k;
    cin >> n >> m >> k;
    int t = (n * k + m - 1) / m;
    vector<vector<int>> ans(t, vector<int> (n));
    vector<int> u(m);
    for (int i = 0; i < m; ++i) {
        u[i] = i + 1;
    }
    int x = 0;
    int cnt = 0;
    for (int i = 0; i < t; ++i) {
        if (x != 0 && x % n <= cnt) {
            x += cnt - (x % n) + 1;
            cnt++;
        }
        for (int j = x; j < x + m; ++j) {
            int j2 = j % n;
            ans[i][j2] = u[j- x];
        }
        x += m;
    }
    cout << t << endl;
    for (int i = 0; i < t; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}
