#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<vector<int>> g(MAX);
vector<int> a(MAX), used(MAX), deep(MAX, 1);
bool flag = false;

void dfs(int v, int x) {
    used[v] = 1;
    for (int to : g[v]) {
        if (used[to] == 1) {
            flag = true;
            return;
        }
        if (!used[to] && a[to] <= x) {
            dfs(to, x);
        }
        if (a[to] <= x) {
            deep[v] = max(deep[v], deep[to] + 1);
        }
    }
    used[v] = 2;
}

bool check(int x, int n, long long k) {
    used.assign(MAX, 0);
    deep.assign(MAX, 1);
    flag = false;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        if (a[i] <= x && !used[i]) {
            dfs(i, x);
            ans = max(ans, deep[i]);
            if (flag) break;
        }
    }
    return flag || ans >= k;
}

signed main() {
    int n, p;
    long long k;
    cin >> n >> p >> k;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < p; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back(v);
    }
    int l = 0, r = 1e9 + 1;
    while (l + 1 < r) {
        int m = (l + r) / 2;
        if (check(m, n, k)) {
            r = m;
        } else {
            l = m;
        }
    }
    if (r == 1e9 + 1) {
        cout << -1 << endl;
        return 0;
    }
    cout << r << endl;
    return 0;
}
