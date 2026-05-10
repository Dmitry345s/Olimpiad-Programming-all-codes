#include<bits/stdc++.h>

using namespace std;

int MAX = 250;
vector<vector<int>> g(MAX);
vector<int> used(MAX), pr(MAX, -1);

bool try_kuhn(int v) {
    if (used[v]) return false;
    used[v] = 1;
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
    for (int i = 0; i < n; ++i) {
        int b;
        cin >> b;
        while (b) {
            g[i].push_back(b - 1);
            cin >> b;
        }
    }
    for (int i = 0; i < n; ++i) {
        used.assign(n, 0);
        try_kuhn(i);
    }
    int cnt = 0;
    for (int i = 0; i < m; ++i) {
        if (pr[i] != -1) {
            cnt++;
        }
    }
    cout << cnt << endl;
    for (int i = 0; i < m; ++i) {
        if (pr[i] != -1) {
            cout << pr[i] + 1 << " " << i + 1 << endl;
        }
    }
    return 0;
}
