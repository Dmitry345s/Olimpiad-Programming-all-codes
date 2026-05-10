#include<bits/stdc++.h>

using namespace std;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n, m, t;
    cin >> n >> m >> t;
    vector<int> md(m, m);
    for (int i = 0; i < n; ++i) {
        vector<pair<int, int>> all(m);
        for (int j = 0; j < m; ++j) {
            int u;
            cin >> u;
            all[j] = {u, j};
        }
        sort(all.begin(), all.end());
        for (int j = 0; j < m; ++j) {
            md[all[j].second] = min(md[all[j].second], m - j - 1);
        }
    }
    sort(md.begin(), md.end());
    int ansd = -1;
    for (int i = 0; i < m - 1; ++i) {
        if (md[i] == md[i + 1]) continue;
        int mbd = md[i + 1];
        if (mbd > 0 && i + 1 <= t) {
            ansd = max(ansd, mbd);
        }
    }
    cout << ansd << endl;
    return 0;
}
