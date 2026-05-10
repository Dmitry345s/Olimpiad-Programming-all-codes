#include<bits/stdc++.h>

#define int long long

using namespace std;

const int MAX = 4001;
vector<int> g[MAX];
set<int> st;
int ans[MAX];
int ch[MAX];
int all[MAX][2 * MAX];
int rt;
int unrt;

void dfs(int v, int p, int nbl) {
    nbl += ch[v];
    if (v == rt) {
        fill(all[v], all[v] + 2 * MAX, 0);
    }
    for (int to : g[v]) {
        if (to == p) continue;
        if (v == rt) {
            unrt = to;
            fill(all[to], all[to] + 2 * MAX, 0);
        }
        dfs(to, v, nbl);
    }
    if (v != rt) all[unrt][nbl + MAX]++;
    all[rt][nbl + MAX]++;
    if (v == rt) {
        ans[v] += all[v][MAX] + 1;
        for (int to : g[v]) {
            for (int i = 0; i < 2 * MAX; ++i) {
                int u = i - MAX;
                //cout << to << " " << i << " " << all[to][i] << " " << all[to][MAX - u] << endl;
                ans[v] += all[to][i] * (all[v][MAX - u] - all[to][MAX - u]);
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            ch[j] = -1;
        }
        ch[i] = 0;
        for (int j = i + 1; j < n; ++j) {
            ch[j] = 1;
        }
        rt = i;
        dfs(i, i, 0);
    }
    for (int i = 0; i < n; ++i) {
        cout << ans[i] - 2 << endl;
    }
    return 0;
}
