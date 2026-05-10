#include<bits/stdc++.h>

using namespace std;

const int MAX = 2e5 + 1;
int g[MAX][2];
int y[MAX][2];

void relax(int u, int v, int w) {
    if (g[u][0] < w) {
        g[u][1] = g[u][0];
        y[u][1] = y[u][0];
        g[u][0] = w;
        y[u][0] = v;

    } else if (g[u][1] < w) {
        g[u][1] = w;
        y[u][1] = v;
    }
}

//bitset<MAX> all[MAX][2];

signed main() {
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; ++i) {
        g[i][0] = -1;
        g[i][1] = -1;
        y[i][0] = -1;
        y[i][1] = -1;
    }
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        --u; --v;
        relax(u, v, w);
        relax(v, u, w);
    }
    return 0;
}
