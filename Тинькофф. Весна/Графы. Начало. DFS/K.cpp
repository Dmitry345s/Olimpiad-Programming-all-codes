#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(100000);
vector<bool> used(100000, false);

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            cout << v + 1 << " " << to + 1 << endl;
            dfs(to);
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
    dfs(0);
    return 0;
}
