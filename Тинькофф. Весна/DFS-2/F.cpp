#include<iostream>
#include<vector>
#include<cmath>

using namespace std;

vector<int> used(200, 0);
vector<vector<int>> g(200);

void dfs(int v) {
    used[v] = 1;
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
}
int main() {
    int n;
    cin >> n;
    vector<vector<int>> apples(n, vector<int> (4));
    for (int i = 0; i < n; ++i) {
        cin >> apples[i][0] >> apples[i][1] >> apples[i][2] >> apples[i][3];
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (apples[i][2] >= apples[j][2]) {
                int x = apples[i][0] - apples[j][0];
                int y = apples[i][1] - apples[j][1];
                int r = apples[i][3] + apples[j][3];
                if (r * r >= x * x + y * y) {
                    g[i].push_back(j);
                }
            }
        }
    }
    dfs(0);
    vector<int> ans;
    for (int i = 0; i < n; ++i) {
        if (used[i]) {
            ans.push_back(i);
        }
    }
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
}
