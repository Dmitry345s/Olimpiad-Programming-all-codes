#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
vector<vector<int>> g(MAX);
vector<int> h(MAX), used(MAX);
int ans = 0;

void dfs(int v, int k, int p = 0) {
    int max1 = 0, max2 = 0;
    for (int to : g[v]) {
        if (to == p) continue;
        dfs(to, k, v);
        if (!used[to]) {
            h[v] = max(h[v], h[to] + 1);
            if (h[to] + 1 >= max1) {
                max2 = max1;
                max1 = h[to] + 1;
            } else if (h[to] + 1 >= max2) {
                max2 = h[to] + 1;
            }
        }
    }
    if (max1 == 0) return;
    if (max2 == 0) {
        if (max1 >= k) {
            used[v] = 1;
            ans += 1;
        }
        return;
    }
    if (max1 + max2 - 1 >= k) {
        used[v] = 1;
        ans += 1;
    }
}

signed main() {
    ios::sync_with_stdio(0);
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
    cout << n << endl;
    for (int i = 2; i <= n; ++i) {
        h.assign(n, 1);
        used.assign(n, 0);
        ans = 0;
        dfs(0, i);
        cout << ans << '\n';
    }
    return 0;
}
