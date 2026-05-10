#include<bits/stdc++.h>

using namespace std;

const int MAX = 1e5 + 1;
int a[MAX];
vector<pair<int, int>> g[MAX];
int nsz[MAX];
vector<int> all;
int us[MAX];

void dfs(int v, int p, int c) {
    nsz[v] = a[v];
    for (auto [to, i] : g[v]) {
        if (to == p) continue;
        dfs(to, v, c);
        nsz[v] += nsz[to];
    }
    while ((int)all.size() < 3 && nsz[v] > c) {
        int in = -1;
        int mx = 0;
        for (auto [to, i] : g[v]) {
            if (to == p) continue;
            if (us[i]) continue;
            if (nsz[to] > mx) {
                mx = nsz[to];
                in = i;
            }
        }
        if (in == -1) {
            all.push_back(0);
            all.push_back(0);
            all.push_back(0);
        } else {
            nsz[v] -= mx;
            all.push_back(in);
            us[in] = 1;
        }
    }
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u; --v;
        g[u].push_back({v, i});
        g[v].push_back({u, i});
    }
    int l = 0, r = 1000000001;
    while (l + 1 < r) {
        int c = (l + r) / 2;
        all.clear();
        fill(us, us + n, 0);
        dfs(0, 0, c);
        if ((int)all.size() > 2) {
            l = c;
        } else {
            r = c;
        }
    }
    all.clear();
    fill(us, us + n, 0);
    dfs(0, 0, r);
    if ((int)all.size() == 0) {
        cout << 1 << " " << 2 << endl;
    } else if ((int)all.size() == 1) {
        cout << all[0] + 1 << " ";
        for (int i = 0; i < n - 1; ++i) {
            if (i != all[0]) {
                cout << i + 1 << endl;
                break;
            }
        }
    } else {
        cout << all[0] + 1 << " " << all[1] + 1 << endl;
    }
    return 0;
}
