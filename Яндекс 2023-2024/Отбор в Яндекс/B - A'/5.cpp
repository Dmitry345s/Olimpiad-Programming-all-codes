#include<bits/stdc++.h>
#define int long long

using namespace std;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n; ++i) {
        cin >> b[i];
    }
    vector<vector<pair<int, int>>> g(51);
    int one = 1;
    for (int i = 0; i <= 50; ++i) {
        for (int j = 1; j <= 50; ++j) {
            g[i].push_back({i % j, one << j});
        }
    }
    int rans = 0;
    int j = 51;
    while (j > 0) {
        int ans = 0;
        for (int i = 0; i < n; ++i) {
            set<pair<int, int>> q;
            vector<int> d(51, one << 57);
            d[a[i]] = 0;
            q.insert({d[a[i]], a[i]});
            while (!q.empty()) {
                int v = q.begin()->second;
                q.erase(q.begin());
                for (auto [to, len] : g[v]) {
                    if ((d[v] | len) < d[to]) {
                        q.erase({d[to], to});
                        d[to] = (d[v] | len);
                        q.insert({d[to], to});
                    }
                }
            }
            if (d[b[i]] == one << 57) {
                cout << -1 << endl;
                return 0;
            }
            ans = (ans | d[b[i]]);
        }
        while (j >= 0 && (one << j) > ans) {
            --j;
        }
        if (j >= 0) {
            rans += (one << j);
        }
        for (int i = 0; i <= 50; ++i) {
            for (auto & [to, len] : g[i]) {
                if (len == (one << j)) len = 0;
            }
        }
    }
    cout << rans << endl;
    return 0;
}
