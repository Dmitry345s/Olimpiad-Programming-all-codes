#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;
int now[MAX];
vector<int> g[MAX];
int cnt = 0;
int ch[MAX];
int n;
int sz[MAX];

void dfs1(int v, int p) {
    ch[v] = 1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs1(to, v);
        if (ch[to] == 1) {
            ch[v] = 0;
            swap(now[v], now[to]);
            cnt += 2;
        }
    }
    if (v == 0 && ch[v] == 1) {
        int to = g[v][0];
        swap(now[v], now[to]);
        cnt += 2;
    }
}

set<pair<int, int>> st[MAX];

void dfs2(int v, int p) {
    sz[v] = 1;
    int maxm = 0, in = -1;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs2(to, v);
        sz[v] += sz[to];
        if (sz[to] >= maxm) {
            in = to;
            maxm = sz[to];
        }
    }
    cnt += (2 * min(sz[v], n - sz[v]));
}

signed main() {
    int mode;
    cin >> mode;
    cin >> n;
    for (int i = 0;i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        now[i] = i;
    }
    if (mode == 1) {
        dfs1(0, 0);
    } else {
        dfs2(0, 0);
    }
    vector<int> ans(n);
    for (int i = 0; i < n; ++i) {
        ans[now[i]] = i;
    }
    cout << cnt << endl;
    for (int i = 0; i < n; ++i) {
        cout << ans[i] + 1 << " ";
    }
    cout << endl;
}
