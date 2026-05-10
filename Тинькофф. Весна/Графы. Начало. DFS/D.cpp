#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(100);
vector<bool> used(100, false);
vector<int> component;
bool flag = true;

void dfs(int v, int p = -1) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (to == p) {
            continue;
        }
        if (!used[to]) {
            component.push_back(to);
            dfs(to, v);
        } else {
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
    dfs(0);
    if (component.size() + 1 != n || !flag) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
    }
    return 0;
}
