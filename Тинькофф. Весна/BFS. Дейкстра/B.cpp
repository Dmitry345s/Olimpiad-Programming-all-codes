#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

int main() {
    int n, m, x, y, x1, y1;
    cin >> n >> m >> x >> y >> x1 >> y1;
    vector<vector<char>> field(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> field[i][j];
        }
    }
    vector<vector<pair<int, int>>> g(n * m);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {;
            if (field[i][j] == '#') {
                continue;
            }
            if (i - 1 >= 0) {
                if (field[i - 1][j] == '.') {
                    g[i * m + j].push_back({(i - 1) * m + j , 1});
                } else if (field[i - 1][j] == 'W') {
                    g[i * m + j].push_back({(i - 1) * m + j , 2});
                }
            }
            if (j - 1 >= 0) {
                if (field[i][j - 1] == '.') {
                    g[i * m + j].push_back({i * m + j - 1 , 1});
                } else if (field[i][j - 1] == 'W') {
                    g[i * m + j].push_back({i * m + j - 1 , 2});
                }
            }
            if (i + 1 < n) {
                if (field[i + 1][j] == '.') {
                    g[i * m + j].push_back({(i + 1) * m + j , 1});
                } else if (field[i + 1][j] == 'W') {
                    g[i * m + j].push_back({(i + 1) * m + j , 2});
                }
            }
            if (j + 1 < m) {
                if (field[i][j + 1] == '.') {
                    g[i * m + j].push_back({i * m + j + 1 , 1});
                } else if (field[i][j + 1] == 'W') {
                    g[i * m + j].push_back({i * m + j + 1 , 2});
                }
            }
        }
    }
    int start = (x - 1) * m + y - 1, last = (x1 - 1) * m + y1 - 1;
    vector<int> d(n * m, 1000000000), p(n * m);
    set<pair<int, int>> q;
    d[start] = 0;
    p[start] = -1;
    q.insert({d[start], start});
    while (!q.empty()) {
        int v = q.begin()->second;
        q.erase(q.begin());
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i].first, len = g[v][i].second;
            if (d[v] + len < d[to]) {
                q.erase({d[to], to});
                d[to] = d[v] + len;
                p[to] = v;
                q.insert({d[to], to});
            }
        }
    }
    if (d[last] == 1000000000) {
        cout << -1 << endl;
        return 0;
    }
    cout << d[last] << endl;
    int v = last;
    vector<int> ans;
    ans.push_back(v);
    while (p[v] != -1) {
        ans.push_back(p[v]);
        v = p[v];
    }
    reverse(ans.begin(), ans.end());
    for (int i = 1; i < ans.size(); ++i) {
        if (ans[i] - ans[i - 1] == 1) {
            cout << 'E';
        } else if (ans[i] - ans[i - 1] == -1) {
            cout << 'W';
        } else if (ans[i] - ans[i - 1] == m) {
            cout << 'S';
        } else {
            cout << 'N';
        }
    }
}
