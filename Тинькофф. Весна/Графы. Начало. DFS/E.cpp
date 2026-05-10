#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> g(100000);
vector<bool> used(100000, false);
vector<int> components(100000, -1);

void dfs(int v, int component) {
    used[v] = true;
    for (int to : g[v]) {
        if (!used[to]) {
            components[to] = component;
            dfs(to, component);
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
    int component = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            components[i] = component;
            dfs(i, component);
            component += 1;
        }
    }
    vector<vector<int>> ans(component);
    for (int i = 0; i < n; ++i) {
        ans[components[i]].push_back(i);
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i].size() << endl;
        for (int j = 0; j < ans[i].size(); ++j) {
            cout << ans[i][j] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
