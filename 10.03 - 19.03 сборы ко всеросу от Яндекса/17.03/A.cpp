#include<bits/stdc++.h>

using namespace std;

const int MAX = 4e5 + 1;
vector<int> g[MAX];
int a[MAX];
int h[MAX];
int ans = MAX;
int up[MAX];

void dfs(int v, int p) {
    h[v] = h[p] + 1;
    up[v] = p;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, v);
    }
}

int tr[MAX];

void sl(int v) {
    int cnt = 0;
    int st = h[v];
    int mans = MAX;
    while (cnt < ans) {
        mans = min(tr[v] + cnt, mans);
        tr[v] = min(tr[v], cnt);
        if (v == 0) break;
        v = up[v];
        cnt++;
    }
    ans = min(ans, mans);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        --a[i];
    }
    dfs(0, 0);
    fill(tr, tr + n, n + 2);
    sl(a[0]);
    for (int i = 1; i < n; ++i) {
        sl(a[i]);
        cout << ans << " ";
    }
    cout << endl;
    return 0;
}
