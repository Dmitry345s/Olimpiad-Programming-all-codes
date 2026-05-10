#include<bits/stdc++.h>

using namespace std;

signed main() {
    int n, m;
    cin >> n >> m;
    vector<int> b(m), p(m);
    vector<vector<int>> c(n);
    for (int i = 0; i < m; ++i) {
        cin >> b[i] >> p[i];
        c[b[i]].push_back(i);
    }
    vector<int> d(n, 1e9);
    d[b[0]] = 0;
    set<pair<int, int>> q;
    q.insert({0, b[0]});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (int i = 0; i < (int)c[v].size(); ++i) {
            int k = c[v][i];
            for (int j = v % p[k]; j < n; j += p[k]) {
                int del = abs(v - j) / p[k];
                if (d[j] > d[v] + del) {
                    q.erase({d[j], j});
                    d[j] = d[v] + del;
                    q.insert({d[j], j});
                }
            }
        }
    }
    if (d[b[1]] == 1e9) {
        cout << -1 << endl;
    } else {
        cout << d[b[1]] << endl;
    }
    return 0;
}
