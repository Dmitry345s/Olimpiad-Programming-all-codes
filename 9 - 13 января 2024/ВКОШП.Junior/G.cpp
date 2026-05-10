#include<iostream>
#include<vector>
#include<queue>

using namespace std;

int bfs(vector<vector<int>>& g) {
    vector<int> d(g.size(), 1e9);
    queue<int> q;
    vector<bool> used(g.size(), false);
    q.push(0);
    d[0] = 0;
    used[0] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (!used[to]) {
                d[to] = d[v] + 1;
                used[to] = true;
                q.push(to);
            }
        }
    }
    return d.back();
}

int main() {
    long long n, m, a, b, c;
    cin >> n;
    vector<int> v(n);
    vector <pair<int, int>> num(n, {-1, -1});
    for (int i = 0; i < n; i++) {
        cin >> v[i];
        if (num[v[i] - 1].first != -1) {
            num[v[i] - 1].second = i;
        } else {
            num[v[i] - 1].first = i;
        }
    }
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < n; ++i) {
        //cout << num[i].first << " " << num[i].second << endl;
    }
    for (int i = 0; i < n + 1; ++i) {
        if (i == 0) {
            g[i].push_back(num[v[i] - 1].second + 1);
        } else if (i == n) {
            continue;
        } else {
            if (num[v[i] - 1].second == i) {
                g[i].push_back(num[v[i] - 1].first + 1);
            } else {
                g[i].push_back(num[v[i] - 1].second + 1);
            }
            if (num[v[i - 1] - 1].second == i - 1) {
                g[i].push_back(num[v[i - 1] - 1].first);
            } else {
                g[i].push_back(num[v[i - 1] - 1].second);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j : g[i]) {
            //cout << j << " ";
        }
        //cout << endl;
    }
    int ans = bfs(g);
    cout << ans << endl;
    return 0;
}
