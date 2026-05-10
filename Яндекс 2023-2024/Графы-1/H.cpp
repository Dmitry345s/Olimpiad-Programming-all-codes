#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<vector<int>> g(MAX);
vector<long long> c(MAX);
vector<int> used(MAX);
vector<int> nums;
long long ans = 0;

void dfs(int v) {
    used[v] = 1;
    ans += c[v];
    for (int to : g[v]) {
        if (!used[to]) {
            dfs(to);
        }
    }
    nums.push_back(v);
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> c[i];
    }
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            int b;
            cin >> b;
            --b;
            g[i].push_back(b);
        }
    }
    dfs(0);
    cout << ans << " " << nums.size() << endl;
    for (int i = 0; i < nums.size(); ++i) {
        cout << nums[i] + 1 << " ";
    }
    return 0;
}
