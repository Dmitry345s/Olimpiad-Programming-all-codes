#include<bits/stdc++.h>

using namespace std;

int MAX = 1e5;
map<pair<int, int>, int> mp;
vector<pair<int, int>> mp2(MAX);
vector<vector<int>> g(MAX);
vector<int> used(MAX);

void dfs(int v) {
    used[v] = 1;
    auto [x, y] = mp2[v];
    if (mp.find({x + 1, y}) != mp.end()) {
        int to = mp[{x + 1, y}];
        g[v].push_back(to);
        g[to].push_back(v);
        if (!used[to]) {
            dfs(to);
        }
    }
    if (mp.find({x - 1, y}) != mp.end()) {
        int to = mp[{x - 1, y}];
        g[v].push_back(to);
        g[to].push_back(v);
        if (!used[to]) {
            dfs(to);
        }
    }
    if (mp.find({x, y + 1}) != mp.end()) {
        int to = mp[{x, y + 1}];
        g[v].push_back(to);
        g[to].push_back(v);
        if (!used[to]) {
            dfs(to);
        }
    }
    if (mp.find({x, y - 1}) != mp.end()) {
        int to = mp[{x, y - 1}];
        g[v].push_back(to);
        g[to].push_back(v);
        if (!used[to]) {
            dfs(to);
        }
    }
}

int ln = 18;
vector<vector<int>> up(ln, vector<int> (4 * MAX, 1e9));
vector<int> h(MAX);
vector<int> tin(MAX);
vector<int> eu;
int timer = 0;

void dfs2(int v, int p = 0) {
    used[v] = 1;
    tin[v] = eu.size();
    h[v] = h[p] + 1;
    eu.push_back(h[v]);
    for (int to : g[v]) {
        if (to == p) continue;
        if (used[to]) continue;
        dfs2(to, v);
        eu.push_back(h[v]);
    }
}

vector<int> to(4 * MAX);

void start() {
    int n = eu.size();
    for (int i = 0; i < n; ++i) {
        up[0][i] = eu[i];
    }
    for (int i = 1; i < ln; ++i) {
        for (int j = 0; j < n; ++j) {
            int j2 = j + (1 << (i - 1));
            up[i][j] = up[i - 1][j];
            if (j2 < n) {
                up[i][j] = min(up[i][j], up[i - 1][j2]);
            }
        }
    }
    to[1] = 0;
    for (int i = 2; i < n; ++i) {
        to[i] = to[i / 2] + 1;
    }
}

int lca(int a, int b) {
    int l = min(tin[a], tin[b]), r = max(tin[a], tin[b]);
    int sz = r - l + 1;
    int l2 = r - (1 << to[sz]) + 1;
    return min(up[to[sz]][l], up[to[sz]][l2]);
}

signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        mp[{x, y}] = i;
        mp2[i] = {x, y};
    }
    dfs(0);
    used.assign(n, 0);
    h[0] = -1;
    dfs2(0);
    //return 0;
    start();
    vector<int> last;
    int q;
    cin >> q;
    vector<int> ans(n, 1e9);
    int k = 500;
    for (int i = 0; i < q; ++i) {
        int t;
        cin >> t;
        if (last.size() > k) {
            vector<int> d(n, 1e9);
            queue<int> q;
            for (int j = 0; j < last.size(); ++j) {
                int v = last[j];
                d[v] = 0;
                q.push(v);
            }
            last.clear();
            while (!q.empty()) {
                int v = q.front();
                q.pop();
                for (int to : g[v]) {
                    if (d[to] > d[v] + 1) {
                        d[to] = d[v] + 1;
                        q.push(to);
                    }
                }
            }
            for (int j = 0; j < n; ++j) {
                ans[j] = min(ans[j], d[j]);
            }
        }
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            int v = mp[{x, y}];
            last.push_back(v);
        } else {
            int x, y;
            cin >> x >> y;
            int v = mp[{x, y}];
            int minm = ans[v];
            for (int j = 0; j < last.size(); ++j) {
                int v2 = last[j];
                int sz = h[v] + h[v2] - 2 * lca(v, v2);
                //cout << v << " " << v2 << " " << lca(v, v2) << " " << h[v] << endl;
                minm = min(minm, sz);
            }
            if (minm == 1e9) {
                cout << -1 << endl;
            } else {
                cout << minm << endl;
            }
        }
    }
    return 0;
}
