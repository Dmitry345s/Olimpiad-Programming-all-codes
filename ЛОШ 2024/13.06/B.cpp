#include<bits/stdc++.h>

using namespace std;

int MAX = 2e5;
vector<vector<int>> g(MAX);
vector<int> used(MAX);
vector<array<vector<int>, 2>> now(MAX);
vector<int> h(MAX);
array<int, 3> ans = {-1, -1, -1};
vector<int> ps(MAX);
vector<int> tin(MAX), tout(MAX);
int timer = 0;

void dfs(int v, int p) {
    tin[v] = timer++;
    used[v] = 1;
    h[v] = h[p] + 1;
    ps[v] = p;
    //cout << v << " " << p << endl;
    array<vector<int>, 2> now2;
    for (int to : g[v]) {
        if (to == p) continue;
        if (used[to]) {
            if (h[to] < h[v]) {
                now[to][h[v] % 2].push_back(v);
                now2[h[to] % 2].push_back(to);
            }
            continue;
        }
        now[v][0].clear();
        now[v][1].clear();
        dfs(to, v);
        if (now[v][0].size() > 1) {
            ans = {now[v][0][0], now[v][0][1], v};
        }
        if (now[v][1].size() > 1) {
            ans = {now[v][1][0], now[v][1][1], v};
        }
        if (now[v][(h[v] + 1) % 2].size() > 0) {
            ans = {now[v][(h[v] + 1) % 2][0], v, v};
        }
    }
    if (now2[0].size() > 1) {
        ans = {now2[0][0], now2[0][1], v};
    }
    if (now2[1].size() > 1) {
        ans = {now2[1][0], now2[1][1], v};
    }
    tout[v] = timer++;
}

bool ch(int a, int b) {
    return tin[a] <= tin[b] && tout[a] >= tout[b];
}

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a; --b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    for (int i = 0; i < n; ++i) {
        //cout << i << endl;
        if (!used[i]) {
            dfs(i, i);
            if (ans != array<int, 3>{-1, -1, -1}) {
                break;
            }
        }
    }
    //cout << 0 << endl;
    if (ans == array<int, 3>{-1, -1, -1}) {
        cout << "NO" << endl;
        return 0;
    }
    int a = ans[0];
    vector<int> rans;
    while (!ch(a, ans[1])) {
        rans.push_back(a);
        a = ps[a];
    }
    rans.push_back(a);
    if (ans[1] != ans[2]) {
        rans.push_back(ans[2]);
    }
    int b = ans[1];
    while (b != a) {
        rans.push_back(b);
        b = ps[b];
    }
    cout << "YES" << endl;
    cout << rans.size() << endl;
    for (auto v : rans) {
        cout << v + 1 << " ";
    }
    return 0;
}
