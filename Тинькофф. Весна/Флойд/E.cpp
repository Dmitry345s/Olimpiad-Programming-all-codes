#include<iostream>
#include<vector>

using namespace std;

struct edge{
    long long to, c;
};

struct edge2{
    long long v, to, c;
};

long long MAX = 1e18 + 179;
vector<vector<edge>> g2(2000), g2t(2000);
vector<edge2> g, gt;
vector<int> used(2000), usedt(2000);
int n;

void dfs(int v) {
    used[v] = 1;
    for (int i = 0; i < g2[v].size(); ++i) {
        int to = g2[v][i].to;
        g.push_back({v, to, g2[v][i].c});
        if (!used[to]) {
            dfs(to);
        }
    }
}

void dfs_t(int v) {
    usedt[v] = 1;
    for (int i = 0; i < g2t[v].size(); ++i) {
        int to = g2t[v][i].to;
        gt.push_back({v, to, g2t[v][i].c});
        if (!usedt[to]) {
            dfs_t(to);
        }
    }
}

int main() {
    int m;
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int v, to, c;
        cin >> v >> to >> c;
        --v; --to;
        g2[v].push_back({to, c});
        g2t[to].push_back({v, c});
    }
    dfs(0);
    vector<long long> d(n, -MAX);
    d[0] = 0;
    int x;
    for (int i = 0; i < 3 * n; ++i) {
        x = -1;
        for (int j = 0; j < g.size(); ++j) {
            if (d[g[j].to] < d[g[j].v] + g[j].c) {
                d[g[j].to] = d[g[j].v] + g[j].c;
                x = g[j].to;
            }
        }
    }
    dfs_t(n - 1);
    vector<long long> dt(n, -MAX);
    dt[n - 1] = 0;
    int y;
    for (int i = 0; i < 3 * n; ++i) {
        y = -1;
        for (int j = 0; j < gt.size(); ++j) {
            if (d[gt[j].to] < d[gt[j].v] + gt[j].c) {
                d[gt[j].to] = d[gt[j].v] + gt[j].c;
                y = gt[j].to;
            }
        }
    }
    if (!used[n - 1]) {
        cout << ":(" << endl;
        return 0;
    }
    if (x != -1 && y != -1) {
        cout << ":)" << endl;
        return 0;
    }
    cout << d[n - 1] << endl;
    return 0;
}
