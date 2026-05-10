#include<bits/stdc++.h>

using namespace std;

int MAX = 1e3 + 1;
vector<vector<int>> g(MAX);
vector<int> used(MAX), pr(MAX, -1);

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = true;
    for (int to : g[v]) {
        if (pr[to] == -1 || try_kuhn(pr[to])) {
            pr[to] = v;
            return true;
        }
    }
    return false;
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
    }
    for (int i = 0; i < n; ++i) {
        used.assign(n, 0);
        try_kuhn(i);
    }
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (pr[i] == -1) {
            cnt++;
        }
    }
    cout << cnt << endl;
    return 0;
}
