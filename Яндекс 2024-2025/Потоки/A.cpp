#include<bits/stdc++.h>

using namespace std;

struct Edge {
    int to, cap, fl;
    Edge(int to = 0, int cap = 0, int fl = 0) : to(to), cap(cap), fl(fl) {}
};

const int MAX = 102;
vector<Edge> all;
vector<int> g[MAX];

int add_edge(int a, int b, int c, int t) {
    Edge sr = Edge(b, c, 0);
    Edge rev = Edge(a, 0, 0);
    if (t == 2) {
        rev.cap = c;
    }
    int x = (int)all.size();
    all.push_back(sr);
    all.push_back(rev);
    return x;
}

int t;
const int INF = 5e7 + 1;
int ans = 0;
int pr[MAX];
int used[MAX];

int dfs(int v, int flow) {
    if (v == t) return flow;
    used[v] = 1;
    int sum = 0;
    for (int i = 0; i < (int)g[v].size() && flow > 0; ++i) {
        Edge now = all[g[v][i]];
        if (used[now.to]) continue;
        if (now.cap - now.fl == 0) continue;
        int x = dfs(now.to, min(flow, now.cap - now.fl));
        all[g[v][i]].fl += x;
        all[(g[v][i] ^ 1)].fl -= x;
        flow -= x;
        sum += x;
    }
    return sum;
}

signed main() {
    int n, m;
    cin >> n >> m;
    t = n - 1;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        int x = add_edge(a, b, c, 2);
        g[a].push_back(x);
        g[b].push_back((x ^ 1));
    }
    ans = 0;
    int x = 0;
    while (true) {
        x = dfs(0, INF);
        if (x != 0) {
            ans += x;
            fill(used, used + n, 0);
        } else {
            break;
        }
    }
    cout << ans << endl;
    for (int i = 0; i < 2 * m; i += 2) {
        cout << all[i].fl << endl;
    }
    return 0;
}
