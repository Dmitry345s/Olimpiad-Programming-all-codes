#include<bits/stdc++.h>

using namespace std;

struct edge {
    int to, c;
};

int MAX = 1e5;
vector<vector<edge>> g(MAX);
vector<long long> ans(MAX);
vector<int> sz(MAX);
int n;
long long sum = 0;

void dfs(int v, int p) {
    sz[v] = 1;
    for (auto [to, c] : g[v]) {
        if (to == p) continue;
        dfs(to, v);
        sz[v] += sz[to];
        sum += sz[to] * (long long) c;
    }
}

void dfs2(int v, int p, long long num) {
    ans[v] = num;
    for (auto [to, c] : g[v]) {
        if (to == p) continue;
        num -= sz[to] * (long long) c;
        num += (n - sz[to]) * (long long) c;
        dfs2(to, v, num);
        num += sz[to] * (long long) c;
        num -= (n - sz[to]) * (long long) c;
    }
}

signed main() {
    cin >> n;
    for (int i = 0; i < n - 1; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        g[a].push_back({b, c});
        g[b].push_back({a, c});
    }
    dfs(0, 0);
    dfs2(0, 0, sum);
    for (int i = 0; i < n; ++i) {
        cout << ans[i] << " ";
    }
    return 0;
}
