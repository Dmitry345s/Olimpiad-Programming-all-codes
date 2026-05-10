#include<bits/stdc++.h>

using namespace std;

const int MAX = 300 * 300 + 2;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
int timer = 1;
vector<int> now_pair(MAX, -1);

bool try_kuhn(int v) {
    if (used[v] == timer) return 0;
    used[v] = timer;
    for (int to : g[v]) {
        if (now_pair[to] == -1) {
            now_pair[to] = v;
            return 1;
        }
    }
    for (int to : g[v]) {
        if (try_kuhn(now_pair[to])) {
            now_pair[to] = v;
            return 1;
        }
    }
    return 0;
}

signed main() {
    int n, m, a, b;
    cin >> n >> m >> a >> b;
    vector<vector<char>> f(n, vector<char> (m));
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> f[i][j];
            if (f[i][j] == '*') cnt++;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (f[i][j] == '*' && i + 1 < n && f[i + 1][j] == '*') {
                g[i * m + j].push_back((i + 1) * m + j);
                g[(i + 1) * m + j].push_back(i * m + j);
            }
            if (f[i][j] == '*' && j + 1 < m && f[i][j + 1] == '*') {
                g[i * m + j].push_back(i * m + j + 1);
                g[i * m + j + 1].push_back(i * m + j);
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = i % 2; j < m; j += 2) {
            //if (f[i][j] == '.') continue;
            if (try_kuhn(i * m + j)) {
                timer++;
            }
        }
    }
    cout << min(b * cnt, a * (timer - 1) + b * (cnt - 2 * (timer - 1))) << endl;
    return 0;
}
