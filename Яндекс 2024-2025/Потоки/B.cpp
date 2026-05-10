#include<bits/stdc++.h>

# define int long long

using namespace std;

struct Edge {
    int to, cap;
    Edge(int to = 0, int cap = 0) : to(to), cap(cap) {}
};

const int MAX = 5e2 + 1, INF = 1e18;
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

int d[MAX], used[MAX];
int n;

int bfs() {
    for (int i = 0; i < n; ++i) {
        d[i] = MAX;
        used[i] = 0;
    }
    d[0] = 0;
    queue<int> q;
    q.push(0);
    used[0] = 1;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            Edge now = all[to];
            if (!used[now.to] && now.cap > 0) {
                d[now.to] = d[v] + 1;
                q.push(now.to);
                used[now.to] = 1;
            }
        }
    }
    if (d[n - 1] != MAX) return d[n - 1];
    return 0;
}

int pr[MAX];

int dfs(int v, int flow) {
    if (v == n - 1) return flow;
    int sum = 0;
    //cout << v << endl;
    for (; pr[v] < (int)g[v].size() && flow > 0; ++pr[v]) {
        if (d[v] >= d[all[g[v][pr[v]]].to]) continue;
        int x = dfs(all[g[v][pr[v]]].to, min(flow, all[g[v][pr[v]]].cap));
        all[g[v][pr[v]]].cap -= x;
        all[(g[v][pr[v]] ^ 1)].cap += x;
        flow -= x;
        sum += x;
        if (x > 0) {
            pr[v]--;
        }
    }
    return sum;
}

signed main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        int x = add_edge(a, b, c);
        g[a].push_back(x);
        g[b].push_back((x ^ 1));
    }
    int ans = 0;
    while (bfs()) {
        //cout << 0 << endl;
        fill(pr, pr + n, 0);
        int x = dfs(0, INF);
        ans += x;
    }
    cout << ans << endl;
    return 0;
}
