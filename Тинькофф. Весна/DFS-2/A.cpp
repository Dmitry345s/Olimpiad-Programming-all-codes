#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(100000);
vector<int> used(100000, 0);
vector<int> tsort(100000);
bool flag = true;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (tsort[to] < tsort[v]) {
            flag = false;
        }
        if (!used[to]) {
            dfs(to);
        }
    }
}
int main() {
    int n, m;
    cin >> n >> m;
    for (int l = 0; l < m; ++l) {
        int i, j;
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
    }
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        tsort[x - 1] = i;
    }
    for (int i = 0; i < n; ++i) {
        if (!used[i]) {
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
