#include<bits/stdc++.h>

using namespace std;

const int MAX = 5e5 + 1;
vector<int> g[MAX];
vector<int> leaves;

void dfs(int v, int p) {
    if ((int)g[v].size() == 1) {
        leaves.push_back(v);
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
}

signed main() {
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    int r = 0;
    for (int i = 0; i < n; ++i) {
        if ((int)g[i].size() != 1) {
            r = i;
            break;
        }
    }
    dfs(r, r);
    vector<int> ch((int)leaves.size());
    vector<pair<int, int>> ans;
    int C = ((int)leaves.size() + 1) / 2;
    for (int i = 0; i < (int)leaves.size(); ++i) {
        int j = (i + C) % (int)leaves.size();
        if (ch[i] == 1) continue;
        ch[i] = 1;
        ch[j] = 1;
        ans.push_back({leaves[i], leaves[j]});
    }
    cout << (int)ans.size() << endl;
    for (auto [u, v] : ans) {
        cout << u + 1 << " " << v + 1 << endl;
    }
    return 0;
}
