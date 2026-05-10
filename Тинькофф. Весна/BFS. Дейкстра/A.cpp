#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    int now;
    vector<vector<int>> g(n);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> now;
            if (now == 1) {
                g[i].push_back(j);
            }
        }
    }
    queue<int> q;
    vector<int> d(n, -1);
    vector<bool> used(n, false);
    q.push(x - 1);
    d[x - 1] = 0;
    used[x - 1] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (!used[to]) {
                used[to] = true;
                q.push(to);
                d[to] = d[v] + 1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        cout << d[i] << " ";
    }
}
