#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(100);
vector<int> used(100, 0);
bool flag = true;

void dfs(int v, int p = -1) {
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (used[to] == 0) {
            used[to] = -used[v];
            dfs(to, v);
        } else if (used[to] == used[v]) {
            flag = false;
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    int i, j;
    for (int l = 0; l < m; ++l) {
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
        g[j - 1].push_back(i - 1);
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == 0) {
            used[i] = 1;
            dfs(i);
        }
    }
    if (flag) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
