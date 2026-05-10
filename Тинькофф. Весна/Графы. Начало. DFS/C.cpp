#include<iostream>
#include<vector>

using namespace std;

vector<bool> used(100, false);
vector<vector<int>> g(100);
vector<int> component;

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            component.push_back(to);
            dfs(to);
        }
    }
}
int main() {
    int n, x;
    cin >> n >> x;
    int now;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> now;
            if (now == 1) {
                g[i].push_back(j);
            }
        }
    }
    dfs(x - 1);
    cout << component.size() + 1 << endl;
    return 0;
}
