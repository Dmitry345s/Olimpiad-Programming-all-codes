#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int to, cap;
    Edge(int to = 0, int cap = 0) : to(to), cap(cap) {}
};

const int MAX = 2e2 + 3, INF = 2e5 + 1;
int n;
vector<Edge> all;
vector<int> g[MAX];

int add_edge(int a, int b, int c) {
    Edge sr = Edge(b, c);
    Edge rev = Edge(a, 0);
    int x = (int)all.size();
    all.push_back(sr);
    all.push_back(rev);
    return x;
}

int used[MAX];

int dfs(int v, int flow) {
    used[v] = 1;
    //cout << v << " ";
    if (v == n + 1) return flow;
    for (int to : g[v]) {
        if (!used[all[to].to] && all[to].cap > 0) {
            int x = dfs(all[to].to, min(flow, all[to].cap));
            all[to].cap -= x;
            all[(to ^ 1)].cap += x;
            if (x > 0) {
                return x;
            }
        }
    }
    return 0;
}

signed main() {
    cin >> n;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int u;
        cin >> u;
        if (u <= 0) {
            int x = add_edge(i, n + 1, -u);
            g[i].push_back(x);
            g[n + 1].push_back((x ^ 1));
        } else {
            sum += u;
            int x = add_edge(n, i, u);
            g[n].push_back(x);
            g[i].push_back((x ^ 1));
        }
    }
    for (int i = 0; i < n; ++i) {
        int c;
        cin >> c;
        for (int j = 0; j < c; ++j) {
            int v;
            cin >> v;
            --v;
            int x = add_edge(i, v, INF);
            g[i].push_back(x);
            g[v].push_back((x ^ 1));
        }
    }
    int ans = 0;
    while (true) {
        int x = dfs(n, INF);
        //cout << x << endl;
        if (x != 0) {
            fill(used, used + n + 2, 0);
            ans += x;
        } else {
            break;
        }
    }
    //cout << ans << endl;
    cout << sum - ans << endl;
    return 0;
}
