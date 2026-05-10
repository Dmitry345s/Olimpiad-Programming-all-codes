#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e6, LN = 18;
vector<vector<int>> g(MAX), up(MAX, vector<int> (LN, 0));
vector<int> tin(MAX), tout(MAX), c(MAX);
int timer = 0;

void dfs(int v = 0, int p = 0) {
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i < LN; ++i) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

int lca(int a, int b) {
    if (ch(a, b)) return a;
    for (int i = LN - 1; i >= 0; --i) {
        if (!ch(up[a][i], b)) {
            a = up[a][i];
        }
    }
    return up[a][0];
}

vector<int> pl(MAX), ans(MAX);

void dfs2(int v = 0, int p = 0) {
    ans[v] = pl[v];
    //cout << v << " " << pl[v] << endl;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs2(to, v);
        ans[v] += ans[to];
    }
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    int r = -1;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p >> c[i];
        if (p == 0) {
            r = i;
            continue;
        }
        --p;
        g[p].push_back(i);
    }
    dfs(r, r);
    //cout << 1 << endl;
    vector<vector<pair<int, int>>> all(n + 1);
    for (int i = 0; i < n; ++i) {
        all[c[i]].push_back({tin[i], i});
    }
    for (int i = 1; i <= n; ++i) {
        //cout << i << endl;
        sort(all[i].begin(), all[i].end());
        if ((int)all[i].size() == 0) continue;
        for (int j = 0; j < (int)all[i].size() - 1; ++j) {
            pl[all[i][j].second]++;
            pl[lca(all[i][j].second, all[i][j + 1].second)]--;
        }
        pl[all[i].back().second]++;
    }
    dfs2(r, r);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
