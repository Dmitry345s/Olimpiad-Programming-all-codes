#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> d(n, 1e9);
    vector<int> p(n);
    vector<bool> used(n, false);
    queue<int> q;
    for (int i = 0; i < k; ++i) {
        int x;
        cin >> x;
        q.push(x - 1);
        d[x - 1] = 0;
        p[x - 1] = x;
        used[x - 1] = true;
    }
    vector<vector<int>> g(n);
    int m;
    cin >> m;
    for (int l = 0; l < m; ++l) {
        int i, j;
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i];
            if (!used[to]) {
                d[to] = d[v] + 1;
                p[to] = p[v];
                used[to] = true;
                q.push(to);
            } else if (d[to] == d[v] + 1 && p[v] < p[to]) {
                p[to] = p[v];
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < n; ++i) {
        cout << p[i] << " ";
    }
    return 0;
}
