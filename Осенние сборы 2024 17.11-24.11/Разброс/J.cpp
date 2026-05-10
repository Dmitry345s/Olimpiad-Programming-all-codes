#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e3;
vector<vector<int>> g(MAX);
vector<vector<int>> ch(MAX, vector<int> (MAX));
vector<int> ans;

void solve(int v) {
    vector<int> s;
    s.push_back(v);
    while (!s.empty()) {
        int u = s.back();
        int flag = 1;
        while ((int)g[u].size() > 0 && ch[g[u][0]][u] == 0) {
            swap(g[u][0], g[u].back());
            g[u].pop_back();
        }
        if ((int)g[u].size() > 0) {
            ch[g[u][0]][u]--;
            ch[u][g[u][0]]--;
            s.push_back(g[u][0]);
            swap(g[u][0], g[u].back());
            g[u].pop_back();
        } else {
            ans.push_back(u);
            s.pop_back();
        }
    }
}

signed main() {
    int n;
    cin >> n;
    int st = 0;
    for (int i = 0; i < n; ++i) {
        int m;
        cin >> m;
        for (int j = 0; j < m; ++j) {
            int to, c;
            cin >> to >> c;
            --to;
            g[i].push_back(to);
            ch[i][to]++;
        }
        if (m % 2 == 1) {
            st = i;
        }
    }
    solve(st);
    cout << (int)ans.size() - 1 << endl;
    for (int i = 0; i < (int)ans.size(); ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
