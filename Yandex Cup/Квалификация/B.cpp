#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int _;
    cin >> _;
    while (_--) {
        int n, m;
        cin >> n >> m;
        vector<vector<char>> f1(n, vector<char> (m));
        vector<vector<char>> f2(n, vector<char> (m));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> f1[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> f2[i][j];
            }
        }
        vector<vector<int>> all(n, vector<int> (m));
        for (int j = 0; j < m; ++j) {
            for (int i = 0; i < n; ++i) {
                if (i == 0) {
                    all[i][j] = (f1[i][j] == f2[i][j]);
                } else {
                    if (f1[i][j] != f2[i][j]) {
                        all[i][j] = 0;
                    } else {
                        all[i][j] = all[i - 1][j] + 1;
                    }
                }
            }
        }
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            vector<pair<int, int>> st;
            st.push_back({-1, -1});
            for (int j = 0; j < m; ++j) {
                while (!st.empty() && st.back().first > all[i][j]) {
                    int y = st.back().first;
                    st.pop_back();
                    ans = max(ans, y * (j - st.back().second - 1));
                }
                st.push_back({all[i][j], j});
            }
            while (!st.empty() && st.back().first > -1) {
                int y = st.back().first;
                st.pop_back();
                ans = max(ans, y * (m - st.back().second - 1));
            }
        }
        cout << ans << endl;
    }
    return 0;
}
