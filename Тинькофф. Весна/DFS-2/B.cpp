#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

vector<vector<int>> g(100000);
vector<int> used(100000, 0);
vector<int> ans;
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
    ans.push_back(v);
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
        if (used[i] == 0) {
            dfs(i);
        }
    }
    if (!flag) {
        cout <<  -1 << endl;
    } else {
        reverse(ans.begin(), ans.end());
        for (int i = 0; i < ans.size(); ++i) {
            cout << ans[i] + 1 << " ";
        }
    }
    return 0;
}
