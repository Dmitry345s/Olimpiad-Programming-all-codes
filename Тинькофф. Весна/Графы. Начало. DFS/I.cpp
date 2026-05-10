#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(100);
vector<bool> used(100, false);

void dfs(int v) {
    used[v] = true;
    for (int i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to]) {
            dfs(to);
        }
    }
}
int main() {
    int n;
    cin >> n;
    int j;
    for (int i = 0; i < n; ++i) {
        cin >> j;
        g[i].push_back(j - 1);
        g[j - 1].push_back(i);
    }
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
            ans += 1;
            dfs(i);
        }
    }
    cout << ans << endl;
    return 0;
}
