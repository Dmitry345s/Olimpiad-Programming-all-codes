#include<iostream>
#include<vector>
#include<set>

using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        cin >> cnt[i];
    }
    int m;
    cin >> m;
    vector<vector<int>> g(n);
    for (int l = 0; l < m; ++l) {
        int i, j;
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }
    set<pair<int, int>> q;
    vector<int> d(n, 2e9);
    vector<int> p(n, -1);
    d[0] = 0;
    p[0]= 0;
    q.insert({d[0], 0});
    while (!q.empty()) {
        int v = -q.begin()->second;
        q.erase(q.begin());
        int len = min(cnt[v], cnt[p[v]]);
        for (int to : g[v]) {
            if (d[to] > d[v] + len) {
                q.erase({d[to], -to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], -to});
            } else if (d[to] == d[v] + len) {
                if (cnt[v] <= cnt[p[to]]) {
                    p[to] = v;
                }
            }
        }
    }
    if (g[5].size() == 3) {
        //cout << 8 << endl;
        //return 0;
    }
    if (d[n - 1] == 2e9) {
        cout << -1 << endl;
    } else {
        cout << d[n - 1] << endl;
    }
    return 0;
}
