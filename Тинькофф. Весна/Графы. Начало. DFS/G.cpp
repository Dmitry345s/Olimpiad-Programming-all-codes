#include<iostream>
#include<vector>

using namespace std;

vector<vector<int>> g(100000);
vector<int> used(100000, 0);
bool flag = true;

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to] == 0) {
            dfs(to);
        } else if (used[to] == 1) {
            flag = false;
        }
    }
    used[v] = -1;
}

int main() {
    int n, m;
    cin >> n >> m;
    int i, j;
    for (int l = 0; l < m; ++l) {
        cin >> i >> j;
        g[i - 1].push_back(j - 1);
    }
    for (int i = 0; i < n; ++i) {
        if (used[i] == 0) {;
            dfs(i);
        }
    }
    if (flag) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
    }
    return 0;
}
