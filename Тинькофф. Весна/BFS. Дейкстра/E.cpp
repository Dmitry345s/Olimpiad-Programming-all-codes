#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> field(n + 2, vector<int> (m + 2, 1));
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            cin >> field[i][j];
        }
    }
    vector<vector<pair<int, int>>> g(n * m);
    vector<vector<int>> a(n + 2);
    for (int i = 0; i < n + 2; ++i) {
        for (int j = 0; j < m + 2; ++j) {
            if (field[i][j] == 1) {
                a[i].push_back(j);
            }
        }
    }
    for (int i = 1; i < n + 1; ++i) {
        int k = 0;
        int check = 0;
        int b = 0;
        int j1 = 1;
        while (j1 < m + 1) {
            while (field[i][j1] < 1) {
                ++j1;
            }
            if (field[i][j1] == 1) {
                for (int l = max(b + 1, a[i][k]); l < j1; ++l) {
                    g[(i - 1) * m + l - 1].push_back({(i - 1) * m + a[i][k], check});
                    g[(i - 1) * m + l - 1].push_back({(i - 1) * m + a[i][k + 1] - 2, 0});
                }
                k += 1;
            } else if (field[i][j1] == 2) {
                for (int l = max(b + 1, a[i][k]); l < j1; ++l) {
                    g[(i - 1) * m + l - 1].push_back({(i - 1) * m + a[i][k], check});
                    g[(i - 1) * m + l - 1].push_back({(i - 1) * m + a[i][k + 1] - 2, 1});
                }
                check = 1;
                b = j1;
            }
            j1 += 1;
        }
    }
    vector<vector<int>> c(m + 2);
    for (int j = 0; j < m + 2; ++j) {
        for (int i = 0; i < n + 2; ++i) {
            if (field[i][j] == 1) {
                c[j].push_back(i);
            }
        }
    }
    for (int j = 1; j < m + 1; ++j) {
        int k = 0;
        int check = 0;
        int b = 0;
        int i1 = 1;
        while (i1 < n + 1) {
            while (field[i1][j] < 1) {
                ++i1;
            }
            if (field[i1][j] == 1) {
                for (int l = max(b + 1, c[j][k]); l < i1; ++l) {
                    g[(l - 1) * m + j - 1].push_back({c[j][k] * m + j - 1, check});
                    g[(l - 1) * m + j - 1].push_back({(c[j][k + 1] - 2) * m + j - 1, 0});
                }
                k += 1;
            } else if (field[i1][j] == 2) {
                for (int l = max(b + 1, c[j][k]); l < i1; ++l) {
                    g[(l - 1) * m + j - 1].push_back({c[j][k] * m + j - 1, check});
                    g[(l - 1) * m + j - 1].push_back({(c[j][k + 1] - 2) * m + j - 1, 1});
                }
                check = 1;
                b = i1;
            }
            i1 += 1;
        }
    }
    queue<int> q;
    vector<int> d(n * m);
    vector<int> ans;
    vector<bool> used(n * m, false);
    q.push(0);
    d[0] = 0;
    used[0] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < g[v].size(); ++i) {
            int to = g[v][i].first, ch = g[v][i].second;
            if (!used[to]) {
                used[to] = true;
                d[to] = d[v] + 1;
                q.push(to);
                if (ch == 1) {
                    ans.push_back(d[to]);
                }
            }
        }
    }
    sort(ans.begin(), ans.end());
    if (ans.size() < 1) {
        cout << 2 << endl;
    } else {
        cout << ans[0] << endl;
    }
}
