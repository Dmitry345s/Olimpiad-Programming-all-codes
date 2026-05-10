#include<iostream>
#include<vector>
#include<algorithm>
#include<set>

using namespace std;

vector<int> d(8000000, 0);
vector<int> used(8000000, 0);
int ans = 0;

void dfs (int i, int j, vector<vector<char>>& a, int i2 = -1, int j2 = -1) {
    int m = a[0].size();
    int n = a.size();
    if (i >= 0 && j >= 0 && i < n && j < m && used[i * m + j] == 1) {
        d[i * m + j] = -1;
    } else if (i >= 0 && j >= 0 && i < n && j < m && used[i * m + j] == -1 && i2 >= 0 && j2 >= 0 && i2 < n && j2 < m) {
        d[i2 * m + j2] = 0;
    } else {
        if (i < n && j < m && i >= 0 && j >= 0) {
            used[i * m + j] = 1;
            int v = i * m + j;
            if (a[i][j] == 'N') {
                dfs(i - 1, j, a, i, j);
                d[v] = min(d[v], d[(i - 1) * m + j]);
            } else if (a[i][j] == 'S') {
                dfs(i + 1, j, a, i, j);
                d[v] = min(d[v], d[(i + 1) * m + j]);
            } else if (a[i][j] == 'E') {
                dfs(i, j + 1, a, i, j);
                d[v] = min(d[v], d[i * m + j + 1]);
            } else if (a[i][j] == 'W') {
                dfs(i, j - 1, a, i, j);
                d[v] = min(d[v], d[i * m + j - 1]);
            }
        }
        if (i < n && j < m && i >= 0 && j >= 0 && d[i * m + j] == 0) {
            ans += 1;
        }
        if (i >= 0 && j >= 0 && i < n && j < m && i2 >= 0 && j2 >= 0 && i2 < n && j2 < m) {
            int v = i * m + j;
            if (a[i2][j2] == 'N') {
                dfs(i - 1, j, a, i, j);
                d[v] = min(d[v], d[(i - 1) * m + j]);
            } else if (a[i2][j2] == 'S') {
                dfs(i + 1, j, a, i, j);
                d[v] = min(d[v], d[(i + 1) * m + j]);
            } else if (a[i2][j2] == 'E') {
                dfs(i, j + 1, a, i, j);
                d[v] = min(d[v], d[i * m + j + 1]);
            } else if (a[i2][j2] == 'W') {
                dfs(i, j - 1, a, i, j);
                d[v] = min(d[v], d[i * m + j - 1]);
            }
        }
    }
    if (i >= 0 && j >= 0 && i < n && j < m) {
        used[i * m + j] = -1;
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<char>> a(n, vector<char> (m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> a[i][j];
            if (a[i][j] == '.') {
                used[i * m + j] = -1;
            }
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (used[i * m + j] == 0) {
                dfs(i, j, a);
            }
        }
    }
    cout << ans << endl;
}
