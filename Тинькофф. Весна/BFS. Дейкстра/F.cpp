#include<iostream>
#include<vector>
#include<set>

using namespace std;

int main() {
    int n;
    cin >> n;
    int b, v;
    cin >> b >> v;
    int r;
    cin >> r;
    vector<vector<vector<int>>> g(n);
    for (int l = 0; l < r; ++l) {
        int i, s, j, e;
        cin >> i >> s >> j >> e;
        g[i - 1].push_back({s, j - 1, e - s});
    }
    vector<int> d(n, 1000000000);
    set<pair<int, int>> q;
    d[b - 1] = 0;
    q.insert({b - 1, d[b - 1]});
    while (!q.empty()) {
        int v = q.begin()->first;
        q.erase(q.begin());
        for (int i = 0; i < g[v].size(); ++i) {
            int start = g[v][i][0], to = g[v][i][1], len = g[v][i][2];
            if (d[v] <= start && d[to] > start + len) {
                q.erase({to, d[to]});
                d[to] = start + len;
                q.insert({to, d[to]});
            }
        }
    }
    if (d[v - 1] != 1000000000) {
        cout << d[v - 1] << endl;
    } else {
        cout << -1 << endl;
    }
}
