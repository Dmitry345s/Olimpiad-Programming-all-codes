#include<bits/stdc++.h>

using namespace std;

int MAXM = 1e5;
vector<int> h(MAXM);
map<vector<int>, int> mp;
int cnt = 0;

void dfs(int v, int p, vector<vector<int>> & g) {
    vector<int> gt;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v, g);
        gt.push_back(h[to]);
    }
    sort(gt.begin(), gt.end());
    if (mp.find(gt) != mp.end()) {
        h[v] = mp[gt];
    } else {
        cnt += 1;
        mp[gt] = cnt;
        h[v] = cnt;
    }
}

signed main() {
    int n, r1, r2;
    cin >> n >> r1 >> r2;
    --r1; --r2;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    dfs(r1, r1, g);
    int ans = h[r1];
    vector<vector<int>> g2(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g2[a].push_back(b);
        g2[b].push_back(a);
    }
    dfs(r2, r2, g2);
    if (h[r2] == ans) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}
