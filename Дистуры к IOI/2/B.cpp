#include<bits/stdc++.h>

#define int long long

using namespace std;

const int INF = 1e18;

signed main() {
    int n;
    cin >> n;
    vector<pair<int, int>> all(n);
    for (int i = 0; i < n; ++i) {
        cin >> all[i].first >> all[i].second;
    }
    vector<array<int, 3>> edg;
    for (int i = 0; i < n - 1; i++) {
        edg.push_back({i, i + 1, abs(all[i].first - all[i + 1].first) + abs(all[i].second - all[i + 1].second)});
    }
    vector<vector<int>> ws(n, vector<int> (n));
    for (int i = 0; i < n; ++i) {
        int cnt = 0;
        for (int j = i + 1; j < n; ++j) {
            cnt += edg[j - 1][2];
            ws[i][j] = cnt;
            ws[j][i] = cnt;
        }
    }
    int ans = INF;
    for (int a = 0; a < n; ++a) {
        for (int b = a + 1; b < n; ++b) {
            int ds = abs(all[a].first - all[b].first) + abs(all[a].second - all[b].second);
            if (ds == ws[a][b]) {
                ans = min(ans, ws[0][n - 1]);
                continue;
            }
            int mn = 0;
            for (int i = a; i < b; ++i) {
                for (int j = i + 1; j <= b; ++j) {
                    int x = min(ws[i][j], ws[i][a] + ws[j][b] + ds);
                    mn = max(x, mn);
                }
            }
            for (int j = a; j <= b; ++j) {
                int x = min(ws[0][j], ws[0][a] + ws[j][b] + ds);
                mn = max(x, mn);
            }
            for (int i = a; i <= b; ++i) {
                int x = min(ws[i][n - 1], ws[i][a] + ws[n - 1][b] + ds);
                mn = max(x, mn);
            }
            int x = min(ws[0][n - 1], ws[0][a] + ws[n - 1][b] + ds);
            mn = max(mn, x);
            ans = min(ans, mn);
        }
    }
    cout << ans << endl;
    return 0;
}
