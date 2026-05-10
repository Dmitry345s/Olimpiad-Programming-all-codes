#include<bits/stdc++.h>

# define int long long

using namespace std;

struct Edge {
    int to, cap, fl, stn;
    Edge(int to = 0, int cap = 0, int fl = 0, int stn = 0) : to(to), cap(cap), fl(fl), stn(stn) {}
};

const int MAX = 5e2 + 1, INF = 1e18;
vector<Edge> all;
vector<int> g[MAX];

int add_edge(int a, int b, int c, int num) {
    Edge sr = Edge(b, c, 0, num);
    Edge rev = Edge(a, 0, 0, num);
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
    used[0] = 1;
    d[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int to : g[v]) {
            if (!used[all[to].to] && all[to].cap - all[to].fl > 0) {
                d[all[to].to] = d[v] + 1;
                q.push(all[to].to);
                used[all[to].to] = 1;
            }
        }
    }
    if (d[n - 1] == MAX) return 0;
    return d[n - 1];
}

int pr[MAX];

int dfs(int v, int flow) {
    if (v == n - 1) return flow;
    int sum = 0;
    for (; pr[v] < (int)g[v].size() && flow > 0; ++pr[v]) {
        if (all[g[v][pr[v]]].cap - all[g[v][pr[v]]].fl <= 0 || d[v] >= d[all[g[v][pr[v]]].to]) continue;
        int x = dfs(all[g[v][pr[v]]].to, min(flow, all[g[v][pr[v]]].cap - all[g[v][pr[v]]].fl));
        all[g[v][pr[v]]].fl += x;
        all[(g[v][pr[v]] ^ 1)].fl -= x;
        flow -= x;
        sum += x;
        if (x > 0) {
            pr[v]--;
        }
    }
    return sum;
}

vector<int> rnow;

int dfs2(int v, int flow) {
    used[v] = 1;
    if (v == n - 1) return flow;
    for (int to : g[v]) {
        Edge now = all[to];
        if (used[now.to] || now.fl <= 0) continue;
        rnow.push_back(now.stn);
        int x = dfs2(now.to, min(now.fl, flow));
        all[to].fl -= x;
        if (x > 0) {
            return x;
        }
        rnow.pop_back();
    }
    return 0;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        --a; --b;
        int x = add_edge(a, b, c, i);
        g[a].push_back(x);
        g[b].push_back((x ^ 1));
    }
    int cnt = 0;
    while (bfs()) {
        fill(pr, pr + n, 0);
        int x = dfs(0, INF);
        cnt += x;
    }
    vector<pair<int, vector<int>>> ans;
    int cnt2 = cnt;
    while (true) {
        rnow.clear();
        fill(used, used + n, 0);
        int x = dfs2(0, INF);
        x = min(x, cnt2);
        if (x == 0) break;
        cnt2 -= x;
        ans.push_back({x, rnow});
    }
    cout << (int)ans.size() << endl;
    for (auto [u, a] : ans) {
        cout << u << " " << (int)a.size() << " ";
        for (auto ind : a) {
            cout << ind + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
