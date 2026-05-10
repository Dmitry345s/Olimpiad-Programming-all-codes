#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> ch(n);
    vector<vector<int>> all(m);
    vector<int> cnt(n);
    queue<int> q;
    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;
        all[i].resize(t);
        for (int j = 0; j < t; ++j) {
            cin >> all[i][j];
            --all[i][j];
            ch[all[i][j]].push_back(i);
        }
        cnt[all[i].back()]++;
        if (cnt[all[i].back()] == 2) {
            q.push(all[i].back());
        }
    }
    int ans = 0;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        ans++;
        for (int u : ch[v]) {
            all[u].pop_back();
            if ((int)all[u].size() != 0) {
                cnt[all[u].back()]++;
                if (cnt[all[u].back()] == 2) {
                    q.push(all[u].back());
                }
            }
        }
    }
    if (ans == n) {
        cout << "Yes" << endl;
    } else {
        cout << "No" << endl;
    }
    return 0;
}
